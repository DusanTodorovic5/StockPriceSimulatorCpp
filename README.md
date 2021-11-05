# Stock Price Simulator in C++ and FLTK

This is stock price simulator made in C++ using FLTK with chart view, and stock trade.
The program simulates users! That means you can buy, sell or admire your stocks.

## Features

StockPriceSimulator features many great functionalities:
 - Downloading stocks in user defined interval
 - Showing stocks on scrollable graph
 - Drawing [EMA](https://www.tradingview.com/scripts/ema/) and [MA](https://www.tradingview.com/scripts/movingaverage/) indicators
 - Simulates buying stocks with specified quantity
 - Features database of all bought stocks
 - Shows user his "walet" with currently owned stocks which he can sell or buy more
 - Shows special table with current stock prices and prices when user bought that stocks, shows their difference and their percent difference
 - User can look up his transaction history

## Built program showcase



https://user-images.githubusercontent.com/79877752/140406132-5c9d4628-85ff-4326-aa5e-0a4b1807282d.mp4



## Dependencies

It uses [cURL](https://curl.se/) for downloading stock prices from yahoo.


## How to run

if you wish to run this program as console, instead of gui, run it with this parameter "--konzola"

Dependencies for running are : [FLTK](https://www.fltk.org/) (Fast Light ToolKit) and [cURL](https://curl.se/)
