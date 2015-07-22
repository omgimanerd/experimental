#!/usr/bin/python
#BECOMES USERPAGE

import cgi
import cgitb
import hashlib
import time

userinput = cgi.FieldStorage()
cgitb.enable()
print "Content-type:text/html\n"

#GET USERDATA
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

#GET POST NUMBER AND LAST POST BY USER
feed = open("data/feed.txt", "r")
lastPostByUser = feed.read()
feed.close()
postNumber = 0
if lastPostByUser != "" and "username" in userinput.keys():
    lastPostByUser = lastPostByUser.split("<>")
    lastPostByUser.pop()
    temp = []
    for i in lastPostByUser:
        temp.append(i.split(","))
    lastPostByUser = temp[::-1]
    postNumber = len(lastPostByUser)
    for i in lastPostByUser:
        if i[0] == userinput["username"].value:
            lastPostByUser = i[1]
            break

#GET TOTAL LIKES BY USER ON LIKED POST
likes = open("data/likes.txt", "r")
likesdata = likes.read()
likes.close()
likesdata = likesdata.split("\n")
likesdata.remove("")
totalLikesByUserOnPost = 0
if ("like" in userinput.keys() or "dislike" in userinput.keys()) and "username" in userinput.keys():
    if "like" in userinput.keys():
        for i in likesdata:
            if i.split(',')[0] == userinput['username'].value and i.split(',')[1] == userinput['like'].value:
                totalLikesByUserOnPost += int(i.split(',')[2])
    else:
        for i in likesdata:
            if i.split(',')[0] == userinput['username'].value and i.split(',')[1] == userinput['dislike'].value:
                totalLikesByUserOnPost += int(i.split(',')[2])
    
#UPDATE LIKES
if ("like" in userinput.keys() or "dislike" in userinput.keys()) and "username" in userinput.keys():
    likes = open("data/likes.txt", "a")
    if "like" in userinput.keys() and totalLikesByUserOnPost == 0:
        likes.write(userinput['username'].value+","+userinput['like'].value+",1\n")
    elif "dislike" in userinput.keys() and totalLikesByUserOnPost == 0:
        likes.write(userinput['username'].value+","+userinput['dislike'].value+",-1\n")
    elif "like" in userinput.keys() and totalLikesByUserOnPost == -1:
        likes.write(userinput['username'].value+","+userinput['like'].value+",2\n")
    elif "dislike" in userinput.keys() and totalLikesByUserOnPost == 1:
        likes.write(userinput['username'].value+","+userinput['dislike'].value+",-2\n")
    likes.close()

#GET ALL LIKES FOR POSTS
likes = open("data/likes.txt", "r")
likesdata = likes.read()
likes.close()
likesdata = likesdata.split("\n")
likesdata.remove("")
likes = {}
for i in likesdata:
    if i.split(',')[1] in likes.keys():
        likes[i.split(',')[1]] += int(i.split(',')[2])
    else:
        likes[i.split(',')[1]] = int(i.split(',')[2])

#UPDATE FEED
def parse(text):
  replace = ["&",     "<",    ">",    '"',      "'",     ",",     "[BOLD]", "[/BOLD]", "[ITALIC]", "[/ITALIC]", "[UNDERLINE]", "[/UNDERLINE]"]
  to =      ["&amp;", "&lt;", "&gt;", "&quot;", "&#x27", "&#44;", "<b>",    "</b>",    "<i>",      "</i>",      "<u>",         "</u>"]
  for i in range(len(replace)):
    text = text.replace(replace[i], to[i])
  return text
if "post" in userinput.keys() and "username" in userinput.keys() and "password" in userinput.keys():
    if parse(userinput['post'].value) != lastPostByUser and len(userinput['post'].value) <= 500  and hashlib.sha256(userinput['password'].value).hexdigest() == passwords[usernames.index(userinput['username'].value)]:
        post = "<div class='users-post'><table>"
        if 'anonymous' in userinput.keys():
            post += "<td class='left'>Anonymous</td>"
        else:
            post += "<td class='left'>"+fullnames[usernames.index(userinput['username'].value)] + ' - ' + userinput['username'].value+"</td>"
        post += "<td class='right'>"+time.strftime("%b")+" "+time.strftime("%d")+" at "+time.strftime("%I")+":"+time.strftime("%M")+" "+time.strftime("%p")+"</td></tr><tr>"
        post += "<td colspan='2'><hr /></td></tr><tr><td colspan='2'><p>"
        post += parse(userinput['post'].value)
        post += "</p><br /></u></b></i></td></tr><tr>"
        post += "<td class='left'><button type='submit' name='like' value='"+str(postNumber)+"'>+1</button>"
        post += "<button type='submit' name='dislike' value='"+str(postNumber)+"'>-1</button></td>"
        post += "\n<>"
        
        feed = open("data/feed.txt", "a")
        feed.write(userinput['username'].value+","+parse(userinput['post'].value)+","+post)
        feed.close()

#GET FULL FEED FOR OUTPUT (ADD LIKE NUMBERS)
feed = open("data/feed.txt", "r")
feedStor = feed.read()
feed.close()
if feedStor != "":
    feedStor = feedStor.split("<>")
    feedStor.remove("")
    for i in range(len(feedStor)):
        feedStor[i] = feedStor[i].split(',')[2]
for i in range(len(feedStor)):
  if str(i) in likes.keys():
    if likes[str(i)] > 0:
      feedStor[i] += "<td class='right'><span class='positive'>Rating: +"+str(likes[str(i)])+"</span></td>"
    elif likes[str(i)] < 0:
      feedStor[i] += "<td class='right'><span class='negative'>Rating: "+str(likes[str(i)])+"</span></td>"
    else:
      feedStor[i] += "<td class='right'><span class='neutral'>Rating: 0</span></td>"
  else:
    feedStor[i] += "<td class='right'><span class='neutral'>Rating: 0</span></td>"
  feedStor[i] += "</tr></table></div>"
feedStor = feedStor[::-1]
    

#HTML BASE
html_BASE1 = """
<!DOCTYPE html>
<html>

<head>
    <title>Dumb Posts</title>
    <link href="data/style.css" rel="stylesheet" type="text/css"/>
  <link rel="icon" href="favicon.ico" type="image/x-icon">
</head>

<body>
  <div id="fb-root"></div>
  <script>(function(d, s, id) {
    var js, fjs = d.getElementsByTagName(s)[0];
    if (d.getElementById(id)) return;
    js = d.createElement(s); js.id = id;
    js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.0";
    fjs.parentNode.insertBefore(js, fjs);
  }(document, 'script', 'facebook-jssdk'));
  </script>
  <a id="top"></a>
  <div class="floater"></div>
  <div id="content-box-user">
    <img src="data/logo.png" class="logo"/>
    <br />
"""
html_EMPTY_FIELD = """
    Please retry, you left a field blank.
    <br />
    <button type="button" onclick="javascript:location.href='index.html';">Return to Login</button>
    </div>
"""
html_CHARACTER_LIMIT_EXCEEDED = """
        Your post has exceeded the character limit of 500 characters.
        <br />
        <button type="button" onclick="window.history.back();">Back</button>
    </div>
"""
html_LOGIN_FAIL = """
        The username or password you entered is incorrect or has not been registered.
        <br />
    <button type="button" onclick="javascript:location.href='index.html';">Return to Login</button>
        <br />
    <button type="button" onclick="javascript:location.href='register.py';">Register</button>
    </div>
"""


html_USERS_LIST = """
    <div id="users-list-box">
      <h2>Registered Users</h2>
      <hr />
"""
for i in fullnames:
  html_USERS_LIST += i+"<br />"
html_USERS_LIST += """
    </div>
"""


html_USERS_FEED = """
    <div id="users-feed">
      <form action="userpage.py" method="POST">
        <h2>Feed</h2>
        <hr />
"""
for i in feedStor:
    html_USERS_FEED += i
html_USERS_FEED += """
        <table id="social-media">
          <tr>
            <td id="facebook">
              <div class="fb-like" data-href="http://homer.stuy.edu/~alvin.lin/finalproject/index.html" data-layout="button_count" data-action="like" data-show-faces="true" data-share="true"></div>  
            </td>
            <td id="twitter">
              <a href="https://twitter.com/share" class="twitter-share-button" data-url="http://homer.stuy.edu/~alvin.lin/finalproject/index.html" data-text="Check out this site!">Tweet</a>
              <script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>
            </td>
          </tr>
        </table>
"""
if 'username' in userinput.keys() and 'password' in userinput.keys():
    html_USERS_FEED += "<input type='hidden' name='username' value='"+userinput['username'].value+"'/>"
    html_USERS_FEED += "<input type='hidden' name='password' value='"+userinput['password'].value+"'/>"
    html_USERS_FEED += """
            </form>
        </div>
    """


html_USERS_SUBMIT = """
    <div id="users-submit">
      <h2>Submit a Post to the Feed</h2>
      <hr />
            <a name="bottom"></a>
      <form name="feed" action="userpage.py" method="POST">
        <table>
          <tr>
            <td>
              <button type="button" onclick="document.feed.post.value += '[BOLD][/BOLD]';"><b>B</b></button>
              <button type="button" onclick="document.feed.post.value += '[ITALIC][/ITALIC]';"><i>I</i></button>
              <button type="button" onclick="document.feed.post.value += '[UNDERLINE][/UNDERLINE]';"><u>U</u></button>
            </td>
                        <td class="users-submit-text">
                            <span>Post anonymously:</span>
                            <input type="checkbox" name="anonymous" value="anonymous"/>
            </td>
          </tr>
          <tr>
            <td colspan="2">
              <textarea wrap="physical" name="post" placeholder="Post a confession or whatever's on your mind!" onkeyup="document.getElementById('charCount').innerHTML = document.feed.post.value.length;"></textarea>
            </td>
          </tr>
          <tr>
            <td>
              <button type="submit">Post</button>
            </td>
                        <td class="users-submit-text">
                            <span>Character count: <span id="charCount">0</span>&#47;500</span>
                        </td>
          </tr>
        </table>
"""
if 'username' in userinput.keys() and 'password' in userinput.keys():
    html_USERS_SUBMIT += "<input type='hidden' name='username' value='"+userinput['username'].value+"'/>"
    html_USERS_SUBMIT += "<input type='hidden' name='password' value='"+userinput['password'].value+"'/>"
    html_USERS_SUBMIT += """
      </form>
    </div>
  </div>
"""


html_FLOATING_LINKS = """
  <div id="fixed-links-floater">
    <button type="button" onclick="javascript:location.href='#bottom';">Post</button>
    <button type="button" onclick="javascript:location.href='account.py';">Account</button>
    <button type="button" onclick="javascript:location.href='about.html';">About Us</button>
    <button type="button" onclick="javascript:location.href='outline.html';">Outline</button>
    <button type="button" onclick="javascript:location.href='http://homer.stuy.edu/~james.chin/game/home.py';">James' Chin</button>
    <button type="button" onclick="window.alert('Successfully logged out.'); javascript:location.href='index.html';">Log Out</button>
  </div>
"""


html_BASE2 = """
  <div class="floater"></div>
</body>

</html>
"""

print html_BASE1
if 'username' in userinput.keys() and 'password' in userinput.keys():
    if userinput['username'].value in usernames and hashlib.sha256(userinput['password'].value).hexdigest() == passwords[usernames.index(userinput['username'].value)]:
        if "post" in userinput.keys():
            if len(userinput['post'].value) > 500:
                print html_CHARACTER_LIMIT_EXCEEDED
            else:
        print "<h2>Welcome, "+fullnames[usernames.index(userinput['username'].value)]+"</h2><hr />"
        print html_USERS_LIST
        print html_USERS_FEED
        print html_USERS_SUBMIT
        print html_FLOATING_LINKS
        else:
      print "<h2>Welcome, "+fullnames[usernames.index(userinput['username'].value)]+"</h2><hr />"
      print html_USERS_LIST
      print html_USERS_FEED
      print html_USERS_SUBMIT
      print html_FLOATING_LINKS
    else:
        print html_LOGIN_FAIL
else:
    print html_EMPTY_FIELD
print html_BASE2