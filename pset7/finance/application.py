from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.hash import pbkdf2_sha256 as pwd_hash
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    portfolio_data = db.execute("SELECT stock, number FROM portfolio WHERE user_id=:user_id ORDER BY stock", user_id=session["user_id"])
    stocks = []
    total = 0
    for stock in portfolio_data:
        result = lookup(stock["stock"])
        stock_entry = {"symbol": result["symbol"], "name": result["name"], "number" : stock["number"], "price": usd(result["price"]), "total": usd(stock["number"]*result["price"])}
        stocks.append(stock_entry)
        total += stock["number"]*result["price"]
    result = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
    cash = result[0]["cash"]
    return render_template("index.html", stocks=stocks, total=usd(total), cash=usd(cash), worth=usd(cash+total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("stock"):
            return apology("Please enter a stock symbol")
        elif not request.form.get("number"):
            return apology("Please enter the number of share you want to buy")
        stock = lookup(request.form.get("stock"))
        if not stock:
            return apology("Please enter a valid stock")
        while True:
            try:
                number = int(request.form.get("number"))
                break
            except ValueError:
                return apology("Please enter a valid number of shares")
                break
        if number <= 0:
            return apology("Please enter a positive number of shares")
        else:
            user_id  = session["user_id"]
            cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = user_id)[0]["cash"]
            inventory_stocks = db.execute("SELECT DISTINCT(stock) FROM log WHERE user_id = :user_id",user_id = user_id)
            cost = number * stock["price"]
            stock = stock["name"]
            unit_cost = cost / number
            if cash >= cost:
                db.execute("INSERT INTO log (user_id, stock, price, number, type) VALUES (:user_id, :stock, :price, :number, 'BUY')", user_id = user_id, stock = stock, price = unit_cost, number = number)
                Exist = False
                for unique_stocks in inventory_stocks:
                    if unique_stocks["stock"] == stock:
                        db.execute("UPDATE portfolio SET number=number+:number WHERE stock=:stock AND user_id=:user_id", user_id = user_id, stock = stock, number = number)
                        Exist = True
                if Exist == False:
                    db.execute("INSERT INTO portfolio (user_id, stock, number) VALUES (:user_id, :stock, :number)", user_id = user_id, stock = stock, number = number)
                db.execute("UPDATE users SET cash=:cash WHERE id = :user_id", cash = cash-cost, user_id = user_id)
                return redirect(url_for("index"))

            else:
                return apology("Not Enough Cash")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    log_data = db.execute("SELECT stock, number, price, time, type FROM log WHERE user_id=:user_id ORDER BY time", user_id=session["user_id"])
    if not log_data:
        return apology("Sorry, no data currently")
    else:
        stocks = []
        for stock in log_data:
            result = lookup(stock["stock"])
            stock_entry = {"type": stock["type"], "stock": result["name"], "number": stock["number"], "price": usd(stock["price"]), "datetime": stock["time"]}
            stocks.append(stock_entry)
        return render_template("history.html", history=stocks)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1:
            return apology("invalid username")
        elif not pwd_hash.verify(request.form.get('password'), rows[0]['hash']):
            return apology("invalid password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
def quote():
    if request.method == "POST":
        """ Check for input """
        if not request.form.get("symbol"):
            return apology("Please Input a Stock Symbol")
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Please Input a Valid Quote")
        else:
            session["symbol"] = quote['symbol']
            session["price"] = quote['price']
            return redirect(url_for("stock"))
    else:
         return render_template("quote.html")

@app.route("/stock", methods=["GET", "POST"])
def stock():
    if request.method == "GET":
        symbol = session.get('symbol', None)
        price = session.get('price', None)
        return render_template("stock.html", symbol=symbol, price=price)
    if request.method == "POST":
        return redirect(url_for("quote"))

@app.route("/register", methods=["GET", "POST"])
def register():

    # forget any user_id
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Please enter a username")

        if not request.form.get("password"):
            return apology("Please enter a password")

        plain_pass = request.form.get("password")
        confirm_pass = request.form.get("confirm_password")

        if plain_pass != confirm_pass:
            return apology("Please re-confirm your password")

        username=request.form.get("username")
        hash_pass = pwd_hash.hash(request.form.get("password"))
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=hash_pass)
        if not result:
            return apology("Sorry, we could not register you")
        else:
            rows = db.execute("SELECT id from users WHERE username=:username", username=username)
            session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("stock"):
            return apology("Please enter a stock")

        if not request.form.get("number"):
            return apology("Please enter the number of stock you want to sell")

        result = lookup(request.form.get("stock"))
        sell_stock = result["name"]
        sell_quantity = int(request.form.get("number"))
        stocks_data = db.execute("SELECT stock, number FROM portfolio")
        validity = False
        while True:
            for stock in stocks_data:
                if sell_stock == stock["stock"]:
                    stock_quantity = stock["number"]
                    validity = True
            break

        if validity == False:
            return apology("Please enter a valid stock")

        if sell_quantity>stock_quantity:
            return apology("Please enter a valid number of stocks")
        gain = result["price"]*sell_quantity
        db.execute("INSERT INTO log (user_id, stock, price, number, type) VALUES (:user_id, :stock, :price, :number, 'SELL')", user_id = session["user_id"], stock = sell_stock, price = result["price"], number = sell_quantity)
        db.execute("UPDATE portfolio SET number=number-:number WHERE stock=:stock AND user_id=:user_id", user_id = session["user_id"], stock = sell_stock, number = sell_quantity)
        db.execute("UPDATE users SET cash=cash+:gain WHERE id=:user_id", gain = gain, user_id = session["user_id"])
        return redirect(url_for("index"))

    else:
        return render_template("sell.html")

@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    if request.method == "POST":
        if request.form["change_btn"]:
            if request.form.get("settings")  == "user":
                return redirect(url_for("change_username"))
            elif  request.form.get("settings")  == "pass":
                return redirect(url_for("change_password"))
        amount = int(request.form.get("amount"))
        if not amount:
            return apology("Please insert a valid amount")
        if request.form["change_btn"] == "add":
            db.execute("UPDATE users SET cash=cash+:amount WHERE id=:user_id", amount = amount, user_id = session["user_id"])
        elif request.form["change_btn"] == "subtract":
            db.execute("UPDATE users SET cash=cash-:amount WHERE id=:user_id", amount = amount, user_id = session["user_id"])
        return redirect(url_for("index"))
    else:
        return render_template("account.html")

@app.route("/change_username", methods=["GET", "POST"])
@login_required
def change_username():
    if request.method == "POST":
        if not request.form.get("new_username") or not request.form.get("confirm_username"):
            return apology("Please complete the fields")

        new_username = request.form.get("new_username")
        confirm_username = request.form.get("confirm_username")

        if new_username != confirm_username:
            return apology("Please re-confirm your username")

        db.execute("UPDATE users SET username=:username WHERE id=:user_id", username = new_username, user_id = session["user_id"])

        # redirect user to home page
        return redirect(url_for("index"))
    else:
        return render_template("change_username.html")

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        if not request.form.get("new_password") or not request.form.get("confirm_password"):
            return apology("Please complete the fields")
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirm_password")

        if new_password != confirm_password:
            return apology("Please re-confirm your password")
        rows = db.execute("SELECT hash FROM users WHERE id=:user_id", user_id=session["user_id"])
        if pwd_hash.verify(old_password, rows[0]['hash']):
            new_hash = pwd_hash.hash(new_password)
            db.execute("UPDATE users SET hash=:new_hash WHERE id=:user_id", new_hash = new_hash, user_id = session["user_id"])
        else:
            return apology("Invalid Password")

        # redirect user to home page
        return redirect(url_for("index"))
    else:
        return render_template("change_password.html")