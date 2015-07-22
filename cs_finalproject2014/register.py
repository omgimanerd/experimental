#!/usr/bin/python

import cgi
import cgitb
import hashlib

userinput = cgi.FieldStorage()
cgitb.enable()
print "Content-type:text/html\n"

userdata = open("data/userdata.txt", "r")
userdataStor = userdata.read()
userdata.close()
userdataStor = userdataStor.split("\n")
userdataStor.remove("")

usernames = []
for i in userdataStor:
  usernames.append(i.split(',')[1])
usernamesJSString = usernames[0]
for i in range(1, len(usernames)):
  usernamesJSString += ","+usernames[i]

def isAlphaNum (char, allowNum):
    if ord(char) >= 65 and ord(char) <= 90:
        return True
    elif ord(char) >= 97 and ord(char) <= 122:
        return True
    elif allowNum and ord(char) >= 48 and ord(char) <= 57:
        return True
    return False
def checkInvalidData (fullname, username, password):
    if fullname.find(',') >= 1 or username.find(',') >= 1 or password.find(',') >= 1:
        return True
    elif fullname.find('\n') >= 1 or username.find('\n') >= 1 or password.find('\n') >= 1:
        return True
    elif len(password) < 6 and len(fullname) > 20 and len(username) > 20:
        return True
    for i in fullname:
        if not isAlphaNum(i, False) and i != " " and i != "-" and i != "'":
            return True
    for i in username:
        if not isAlphaNum(i, True) and i != "_" and i != "-":
            return True
    return False

html_BASE1 = """
<!DOCTYPE html>
<html>
<head>
  <title>Dumb Posts</title>
  <link href="data/style.css" rel="stylesheet" type="text/css"/>
  <link rel="icon" href="favicon.ico" type="image/x-icon">
    <script type="text/javascript">
    function checkFullName() {
        var fullname = document.register.fullname.value;
    var errorField = document.getElementById('errorFullName');
    if (fullname.length <= 20) {
      if (/[^a-zA-Z\x20\x27\x2D]/.test(fullname) || fullname.length == 0) {
        errorField.innerHTML = "Invalid name".fontcolor('#FF3D0D');
      }
      else {
        errorField.innerHTML = "&#x2713;".fontcolor('#00CD66');
      }
    }
    else {
      errorField.innerHTML = "Full name too long".fontcolor('#FF3D0D');
    }
    }
    function checkUsername() {
"""
html_BASE1 += "var usernameList = '"+usernamesJSString+"'.split(',');\n"
html_BASE1 += """
        var username = document.register.username.value;
    var errorField = document.getElementById('errorUsername');
    if (username.length <= 20) {
      if (usernameList.indexOf(username) == -1) {
        if (/[^a-zA-Z0-9\x2D\x5F]/.test(username) || username.length == 0) {
          errorField.innerHTML = "Invalid username".fontcolor('#FF3D0D');
        }
        else {
          errorField.innerHTML = "&#x2713;".fontcolor('#00CD66');
        }
      }
      else {
        errorField.innerHTML = "Username taken".fontcolor('#FF3D0D');
      }
    }
    else {
      errorField.innerHTML = "Username too long".fontcolor('#FF3D0D');
    }
    }
    function checkPassword() {
        var password = document.register.password.value;
    var errorField = document.getElementById('errorPassword');
    if (password.length >= 6) {
      if (password.length <= 20) {
        if (/[^a-zA-Z0-9\x2D\x5F]/.test(password)) {
          errorField.innerHTML = "Invalid password".fontcolor('#FF3D0D');
        }
        else {
          errorField.innerHTML = "&#x2713;".fontcolor('#00CD66');
        }
      }
      else {
        errorField.innerHTML = "Password too long".fontcolor('#FF3D0D');
      }
    }
    else {
      errorField.innerHTML = "Password too short".fontcolor('#FF3D0D');
    }
    }
    function checkConfirmPassword() {
        var password = document.register.password.value;
        var confirmPassword = document.register.confirmPassword.value;
    var errorField = document.getElementById('errorConfirmPassword');
        if (confirmPassword != password) {
            errorField.innerHTML = "Does not match".fontcolor('#FF3D0D');
        }
        else {
            errorField.innerHTML = "&#x2713;".fontcolor('#00CD66');
        }
    }
    </script>
</head>
<body>
  <div class="floater"></div>
  <div id="content-box">
    <img src="data/logo.png" class="logo"/>
"""
html_NAME_TAKEN = """
    Sorry, that username has already been taken.
    <br />
    <button type="button" onclick="window.history.back();">Return to registration</button>
"""
html_NONMATCHING_PASSWORD = """
    Your passwords did not match, please confirm using the correct password.
    <br />
    <button type="button" onclick="window.history.back();">Return to registration</button>
"""
html_INVALID = """
    You entered an invalid username or password. Make sure your full name and username are alphanumeric and that your password is 6 or more characters long.
    <br />
    Full names and usernames may not exceed 20 characters in length.
    <br />
    <button type="button" onclick="window.history.back();">Return to registration</button>
"""
html_EMPTY_FIELD = """
    Please retry, you left a field blank.
    <br />
    <button type="button" onclick="window.history.back();">Return to registration</button>
"""
html_SUCCESS = """
    Registration successful, you may log in with your account now.
    <br />
    <button type="button" onclick="javascript:location.href='index.html';">Return to Login</button>
"""
html_BASEFORM = """
    <form name="register" action="register.py" method="POST">
      <div id="register-form">
        <h2>
        Registration
        </h2>
        <hr />
        Full Name:
        <br />
        <input type="text" name="fullname" onblur="checkFullName();"/><span id="errorFullName"></span>
        <br />
        Username:
        <br />
        <input type="text" name="username" onblur="checkUsername();"><span id="errorUsername"></span>
        <br />
        Password:
        <br />
        <input type="password" name="password" onkeyup="checkPassword();"/><span id="errorPassword"></span>
        <br />
        Confirm Password:
        <br />
        <input type="password" name="confirmPassword" onkeyup="checkConfirmPassword();"/><span id="errorConfirmPassword"></span>
        <br />
        <input type="hidden" name="visited" value="true"/>
        <button type="submit">Register</button>
        <button type="button" onclick="javascript:location.href='index.html';">Return to Login</button>
        <br />
      </div>
    </form>
"""
html_BASE2 = """
  </div>
</body>
</html>  
"""

print html_BASE1
if 'fullname' in userinput.keys() and 'username' in userinput.keys() and 'password' in userinput.keys() and 'confirmPassword' in userinput.keys():
  if userinput['username'].value in usernames:
    print html_NAME_TAKEN
  elif userinput['password'].value != userinput['confirmPassword'].value:
    print html_NONMATCHING_PASSWORD
  elif checkInvalidData(userinput['fullname'].value, userinput['username'].value, userinput['password'].value):
    print html_INVALID
  else:
    userdata = open("data/userdata.txt", "a")
    userdata.write(userinput['fullname'].value+','+userinput['username'].value+','+hashlib.sha256(userinput['password'].value).hexdigest()+'\n')
    userdata.close()
    print html_SUCCESS
elif 'visited' in userinput.keys():
  print html_EMPTY_FIELD
else:
  print html_BASEFORM
print html_BASE2
