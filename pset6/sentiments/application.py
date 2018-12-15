from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    if tweets == None:
        sys.exit("Couldn't get user timeline: Invalid twitter handle")

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    positive_counter=0
    negative_counter=0
    neutral_counter=0

    for i in tweets:
        sentiment=analyzer.analyze(i)
        if sentiment>0:
            positive_counter+=1
        elif sentiment<0:
            negative_counter+=1
        else:
            neutral_counter+=1

        positive, negative, neutral = positive_counter, negative_counter, neutral_counter


    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
