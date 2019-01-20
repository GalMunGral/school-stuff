### When device connects to the Internet:
1. Host broadcasts a DHCP request encapsulated in UDP packet.
2. DHCP server responds with an IP address, name and IP of a DNS server and the first-hop router's IP.

### When navigating to `https://example.com/some/path?key=value`

1. Browser creates a DNS query, encapsulated in UDP packet, encapsulated in IP datagram.
2. Host broadcasts a ARP query for the MAC address of the first-hop router.
3. Router responds with its MAC address; Host stores the MAC addresses in its ARP cache.
4. Host sends out Ethernet/802.11 frame containing the query, which is then forwarded to the DNS server.
5. DNS server responds with the IP address for `example.com`.
6. Host performs a 3-way handshake (SYN, SYN-ACK, ACK) to establish TCP connection with HTTP server.
7. Host performs TLS key exchange with HTTP server and starts an encrypted session.
8. Browser sends out HTTP reqeust `GET /some/path?key=value HTTP/1.1\r\n Host: example.com ...`
9. HTTP server handles the path `some/path` and query key-value pair `(key,value)` and sends back a HTTP response.
10. Browser parses the source code contained in the HTTP response and renders the webpage.
