echo "Input date in dd/mm/yyyy format without any space"
printf "Birthday-1 :- "
read bd1
printf "Birthday-2 :- "
read bd2

wkd1=$(date -f "%m-%d-%Y" "$bd1")
wkd2=$(date -f "%m-%d-%Y" "$bd2")

if [ wkd1 -eq wkd2 ]; then
    echo "Same week day: $wkd1"
else
    echo "Different weekday: $wkd1, $wkd2"
fi
