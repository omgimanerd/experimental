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
fullnames = []
usernames = []
passwords = []
for i in userdataStor:
  fullnames.append(i.split(',')[0])
  usernames.append(i.split(',')[1])
  passwords.append(i.split(',')[2])

def isAlphaNum (char, allowNum):
    if ord(char) >= 65 and ord(char) <= 90:
        return True
    elif ord(char) >= 97 and ord(char) <= 122:
        return True
    elif allowNum and ord(char) >= 48 and ord(char) <= 57:
        return True
    return False
def checkInvalidFullname (fullname):
    if fullname.find(',') >= 1 or fullname.find('\n') >= 1:
        return True
    elif len(fullname) > 20:
        return True
    for i in fullname:
        if not isAlphaNum(i, False) and i != " " and i != "-" and i != "'":
            return True
    return False
def checkInvalidPassword (password):
    if password.find(',') >= 1 or password.find('\n') >= 1:
        return True
    elif len(password) < 6:
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
  
  function revert() {
    field = "<button type='button' onclick='changeFullName()'>Change your fullname</button>";
    field = field.concat("<button type='button' onclick='changePassword()'>Change your password</button>");
    field = field.concat("<button type='button' onclick='deleteAccount()'>Delete account</button>");
    document.getElementById('account-form-morph').innerHTML = field;
  }
  function changeFullName() {
    field = "New Full Name:";
    field = field.concat("<br /><input type='text' name='newFullname' onkeyup='checkFullName();'/><span id='errorNewFullname'></span>");
    field = field.concat("<br /><button type='submit'>Submit</button>");
    field = field.concat("<button type='button' onclick='revert()'>Back</button>");
    document.getElementById('account-form-morph').innerHTML = field;
  }
  function changePassword() {
    field = "New Password:";
    field = field.concat("<br /><input type='password' name='newPassword' onkeyup='checkPassword();'/><span id='errorNewPassword'></span>");
    field = field.concat("<br />Confirm Password:");
    field = field.concat("<br /><input type='password' name='confirmNewPassword' onkeyup='checkConfirmPassword();'/><span id='errorConfirmNewPassword'></span>");
    field = field.concat("<br /><button type='submit'>Submit</button>");
    field = field.concat("<button type='button' onclick='revert()'>Back</button>");
    document.getElementById('account-form-morph').innerHTML = field;
  }
  function deleteAccount() {
    field = "Are you sure you want to delete your account?<br />";
    field = field.concat("<button type='submit' name='delete' value='true'>Confirm</button>");
    field = field.concat("<button type='button' onclick='revert()'>Back</button>");
    document.getElementById('account-form-morph').innerHTML = field;
  }
    function checkFullName() {
        var fullname = document.account.newFullname.value;
    var errorField = document.getElementById('errorNewFullname');
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
    function checkPassword() {
        var password = document.account.newPassword.value;
    var errorField = document.getElementById('errorNewPassword');
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
        var password = document.account.newPassword.value;
        var confirmPassword = document.account.confirmNewPassword.value;
    var errorField = document.getElementById('errorConfirmNewPassword');
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

html_LOGIN_FAIL = """
        The username or password you entered is incorrect or has not been registered.
        <br />
    <button type="button" onclick="javascript:location.href='account.py';">Try Again</button>
"""
html_INVALID_FULLNAME = """
    You entered an invalid full name. Make sure your full name is alphanumeric and does not exceed 20 characters in length.
    <br />
    <button type="button" onclick="javascript:location.href='account.py';">Try Again</button>
"""
html_NONMATCHING_PASSWORD = """
    Your passwords did not match, please confirm using the correct password.
    <br />
    <button type="button" onclick="javascript:location.href='account.py';">Try Again</button>
"""
html_INVALID_PASSWORD = """
    You entered an invalid password. Make sure your password alphanumeric and that your password is 6 or more characters long.
    <br />
    <button type="button" onclick="javascript:location.href='account.py';">Try Again</button>
"""
html_EMPTY_FIELD = """
    Please retry, you left a field blank. You must enter your username and password to change your name or password or delete your account.
    <br />
    <button type="button" onclick="javascript:location.href='account.py';">Try Again</button>
"""
html_SUCCESS_FULLNAME = """
    Name change successful.
    <br />
    <form action="userpage.py" method="POST">
"""
html_SUCCESS_PASSWORD = """
    Password change successful, please log in again.
    <br />
    <button type="button" onclick="javascript:location.href='index.html';">Log In</button>
"""
html_ACCOUNT_DELETED = """
    Your account has been deleted. Thanks for trying out this website.
    <br />
    <button type="button" onclick="javascript:location.href='index.html';">Homepage</button>
"""

html_BASEFORM = """
    <form name="account" action="account.py" method="POST">
      <div id="account-form">
        <h2>
        Account:
        </h2>
        <hr />
        Username:
        <br />
        <input type="text" name="username"/>
        <br />
        Password:
        <br />
        <input type="password" name="password"/>
        <br />
        <div id="account-form-morph">
          <button type="button" onclick="changeFullName()">Change your full name</button>
          <button type="button" onclick="changePassword()">Change your password</button>
          <button type="button" onclick="deleteAccount()">Delete account</button>
        </div>
        <input type="hidden" name="visited" value="true"/>
      </div>
      <button type="button" onclick="window.history.back();">Back</button>
    </form>
"""
html_BASE2 = """
  </div>
</body>
</html>  
"""

print html_BASE1
if 'username' in userinput.keys() and 'password' in userinput.keys() and ("newFullname" in userinput.keys() or ("newPassword" in userinput.keys() and "confirmNewPassword" in userinput.keys()) or "delete" in userinput.keys()):
  if userinput['username'].value in usernames and hashlib.sha256(userinput['password'].value).hexdigest() == passwords[usernames.index(userinput['username'].value)]:
    #userdataStor still exists
    userindex = usernames.index(userinput['username'].value)
    if "newFullname" in userinput.keys():
      if checkInvalidFullname(userinput['newFullname'].value):
        print html_INVALID_FULLNAME
      else:
        userdataStor[userindex] = userinput['newFullname'].value+','+usernames[userindex]+','+passwords[userindex]
        userdataStor = "\n".join(userdataStor)
        userdataStor += "\n"
        userdata = open("data/userdata.txt", "w")
        userdata.write(userdataStor)
        userdata.close()
        html_SUCCESS_FULLNAME += "<input type='hidden' name='username' value='"+userinput['username'].value+"'/>"
        html_SUCCESS_FULLNAME += "<input type='hidden' name='password' value='"+userinput['password'].value+"'/>"
        html_SUCCESS_FULLNAME += "<button type='submit'>Continue to Homepage</button></form>"
        print html_SUCCESS_FULLNAME
    elif "newPassword" in userinput.keys() and "confirmNewPassword" in userinput.keys():
      if userinput['newPassword'].value == userinput['confirmNewPassword'].value:
        if checkInvalidPassword(userinput['newPassword'].value):
          print html_INVALID_PASSWORD
        else:
          userdataStor[userindex] = fullnames[userindex]+','+usernames[userindex]+','+hashlib.sha256(userinput['newPassword'].value).hexdigest()
          userdataStor = "\n".join(userdataStor)
          userdataStor += "\n"
          userdata = open("data/userdata.txt", "w")
          userdata.write(userdataStor)
          userdata.close()
          print html_SUCCESS_PASSWORD
      else:
        print html_NONMATCHING_PASSWORD
    else:
      userdataStor = userdataStor[0:userindex]+userdataStor[userindex+1:]
      userdataStor = "\n".join(userdataStor)
      userdataStor += "\n"
      userdata = open("data/userdata.txt", "w")
      userdata.write(userdataStor)
      userdata.close()
      print html_ACCOUNT_DELETED
  else:
    print html_LOGIN_FAIL
elif 'visited' in userinput.keys():
  print html_EMPTY_FIELD
else:
  print html_BASEFORM
print html_BASE2
