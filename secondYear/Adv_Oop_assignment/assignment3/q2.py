from datetime import date
from calendar import day_name
from random import random

coupons = {dayName: {"coupon": dayName[:5].upper(
) + "567JH", "discount": (10 + int(random()*20))} for dayName in day_name}

my_date = date.today()
currentWeekDay = day_name[my_date.weekday()]

print("Today's coupon code: {coupon} \t (Discount: {discount}%)".format(
    coupon=coupons[currentWeekDay]["coupon"], discount=coupons[currentWeekDay]["discount"]))
