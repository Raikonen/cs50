import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = set()
        self.negatives = set()

        file = open(positives, "r")
        for line in file:
            if not line.startswith(';') or not line.startswith( ' ' ):
                self.positives.add(line.strip("\n"))
        file.close()

        file = open(negatives, "r")
        for line in file:
            if not line.startswith(';') or not line.startswith( ' ' ):
                self.negatives.add(line.strip("\n"))
        file.close()


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        total_score=0
        for i in tokens:
            if i.lower() in self.positives:
                total_score+=1
            elif i.lower() in self.negatives:
                total_score-=1
        return total_score
