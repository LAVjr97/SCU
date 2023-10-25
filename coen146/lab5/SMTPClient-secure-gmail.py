
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server
# the program runs the ping command, and emails the result using smtp.gmail.com

# NOTE: Do not forget to allow login from less secure apps in your gmail account. Otherwise gmail will complain about username and password.


import smtplib, ssl
import subprocess

port = 465  # For SSL
email_address = raw_input("Please enter your email address: ")
password = raw_input("Please enter your password: ")
receiver_email = raw_input("Please enter receiver's email address: ")


# ping google.com and save the result
#popen is basically command line prompt 
command = 'ping -c 2 www.google.com'
ping = subprocess.Popen(command, stdout=subprocess.PIPE)
ping = ping.stdout.read()

print ('\nNow contacting the mail server...') 
connection = smtplib.SMTP_SSL('smtp.gmail.com', port) 
connection.login(email_address, password)

MSG = 'SUBJECT: Results From Ping\r\n '

print ('\nSending email...') 
connection.sendmail(email_address, receiver_email, MSG)
connection.close()


