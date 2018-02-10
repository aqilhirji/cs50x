#!/usr/bin/env python3

import os
import nltk

class Analyzer():

	"""Implements sentiment analysis."""

	def __init__(self, positives, negatives):
		"""Initialize Analyzer."""
		self.positives = set()
		self.negatives = set()

		file0 = open('positive-words.txt', 'r')
		for line in file0: 
			if line.startswith(';'):
				continue
			else: 
				self.positives.add(line.strip())
		file0.close()
		
		#p
		file1 = open('negative-words.txt', 'r')
		for line in file1: 
			if line.startswith(';'):
				continue
			else: 
				self.negatives.add(line.strip())
		file1.close()


	def analyze(self, text):
		"""Analyze text for sentiment, returning its score."""

		score = 0
		tokenizer = nltk.tokenize.TweetTokenizer()
		tokens = tokenizer.tokenize(text)
		for token in tokens: 
			if token.lower() in self.positives: 
				score += 1
			elif token.lower() in self.negatives: 
				score -= 1
			else:
				continue
		return score