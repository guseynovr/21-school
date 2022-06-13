import os

CONTENT_TEXT = "Content-type:text/html\r\n\r\n"
CONTENT_STATUS = "Status: 200 OK\nContent-Type: text/html; charset=utf-8\r\n\r\n"
CONTENT_HTML = "Content-type:text/html\r\n\r\n"
MAIN_PAGE = """
	<html>
	<head>
	<title>21</title>
	</head>
	<body>
	<h2>cgi cyberserv, yeaah!</h2>
	</body>
	</html>
"""
print(CONTENT_STATUS)

for key in sorted(os.environ):
    print(key, "=", f'|{os.environ.get(key)}|')
