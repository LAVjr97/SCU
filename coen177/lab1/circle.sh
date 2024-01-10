# Name: Luis Villalta
# Date: 1/9/24
# Title: Lab1
# Description: This program computes the area of a circle given a radius
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "lvillalta" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
exit 1
fi
response="Yes"
while [ $response != "No" ]
do
        echo "Enter radius of the circle: "
        read radius
        pi=3.1415
        temp=`expr $radius \* $radius`
        echo "The area of the circle is $area"
        echo "$pi * $temp" | bc
        echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done    

