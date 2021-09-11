string="21 fsd sdklfa.sdfs"
read -ra num <<< $string
count=${num[0]}
((count+=1))
echo $count