## Plan

1. test nginx + wordpress methods, body, cgi
2. fix choose_location
3. Cookies and session management (prepare example)
4. Check all todo's and fixme's
5. Testing

---
- Refactor
    - Refactor using SOLID principles
    - Request processing flow
    - refactor Response class
    - mv executing and response filling to method handler

- Cookie
    - Set-Cookie: wordpress_test_cookie=WP+Cookie+check; path=/
    - Set-Cookie: 
        - wordpress_86a9106ae65537651a8e456835b316ab=admin%7C1654614870%7CCktdP8HXAZcrXpZskBwlB877Eg6HFMyhPtlTd1pCoBR%7Cbc54d8abecdd2e8391c3fe10af51fb2bfd789a4a2a81d6598df9eb830b54c897; path=/wp-content/plugins; HttpOnly
    - Set-Cookie:
        - wordpress_86a9106ae65537651a8e456835b316ab=admin%7C1654614870%7CCktdP8HXAZcrXpZskBwlB877Eg6HFMyhPtlTd1pCoBR%7Cbc54d8abecdd2e8391c3fe10af51fb2bfd789a4a2a81d6598df9eb830b54c897; path=/wp-admin; HttpOnly
    - Set-Cookie:
        - wordpress_logged_in_86a9106ae65537651a8e456835b316ab=admin%7C1654614870%7CCktdP8HXAZcrXpZskBwlB877Eg6HFM- yhPtlTd1pCoBR%7C34bf62bc3505fe804b9270567558e031fd26f321fcb721daff10e908ec0a71af; path=/; HttpOnly
    - Cookie: 
        - wordpress_test_cookie=WP+Cookie+check; wordpress_logged_in_86a9106ae65537651a8e456835b316ab=admin%7C1654614870%7CCktdP8HXAZcrXpZskBwlB877Eg6HFMyhPtlTd1pCoBR%7C34bf62bc3505fe804b9270567558e031fd26f321fcb721daff10e908ec0a71af

---

### Some reminders

client_header_buffer_size	1k;
client_header_timeout		60s;

client_max_body_size		1m;
client_body_timeout			60s;

Old subject required headers:
- Accept-Charsets
- Accept-Language
- Allow
- Authorization
- Content-Language
- Content-Length
- Content-Location
- Content-Type
- Date
- Host
- Last-Modified
- Location
- Referer
- Retry-After
- Server
- Transfer-Encoding
- User-Agent
- WWW-Authenticate

Check connection leaks: lsof -i -a -p 29693
    -i for connections only
    -a AND operator
    -p pid
