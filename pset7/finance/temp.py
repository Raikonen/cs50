from cs50 import SQL
db = SQL("sqlite:///finance.db")
rows = db.execute("SELECT stock, number, price, time, type FROM log WHERE user_id=:user_id ORDER BY time", user_id=1)
stocks = []
for stock in rows:
    stock_entry = {"type": stock["type"], "stock": stock["stock"], "number": stock["number"], "price": stock["price"], "datetime": stock["time"]}
    stocks.append(stock_entry)
for row in stocks:
    print(row)