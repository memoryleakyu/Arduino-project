import requests
import serial
import time


headers = {
    'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.117 Safari/537.36'}

arduino = serial.Serial('/dev/cu.usbmodem14401', 9600)
time.sleep(1)

url = 'https://www.okex.me/api/v1/ticker.do?symbol=btc_usdt'

basePrice = 8850.0
coins = 10
targetGain = 0.005
targetLoss = 0.005


def get_latest_crypto_price():
    res = requests.get(url, headers=headers)
    data = res.json()['ticker']
    btcPrice = float(data.get('last'))
    return btcPrice


def main():

    last_price = -1
    while True:

        price = get_latest_crypto_price()
        if price != last_price:
            if price <= basePrice:
                loss = (price - basePrice)/basePrice
                netLoss = coins * (basePrice - price)
                print('current bitcoin price is {}. Your loss is {} dollar'.format(
                    price, netLoss))
                rangeLed = int(loss * 30 / targetLoss)

                if rangeLed <= -30:
                    rangeLed = -30
                if rangeLed == 0:
                    rangeLed = -1

                arduino.write(str(rangeLed))
            if price > basePrice:
                gain = (price - basePrice)/basePrice
                netGain = coins * (price - basePrice)
                print('current bitcoin price is {}. Your gain is {} dollar'.format(
                    price, netGain))
                rangeLed = int(gain * 30 / targetGain)
                if rangeLed >= 30:
                    rangeLed=30
                if rangeLed == 0:
                    rangeLed=1

                arduino.write(str(rangeLed))
            last_price=price
        time.sleep(3)


main()
