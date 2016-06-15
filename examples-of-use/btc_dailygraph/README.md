
<h1>Bitcoin Graph View</h1> (view the current status on the chart)<br />
Example - serial display with Raspberry Pi (get Bitcoin last value)<br />
<img src=https://raw.githubusercontent.com/octopusengine/serial-display/master/images/btc.jpg width=800><br />
<i>red line = 600</i><br />
<br />
<hr />
from https://www.bitstamp.net/api/ticker/ <br />
json: <br />
<i>{"high": "587.09", "last": "583.67", "timestamp": "1465644119", "bid": "583.03", "vwap": "578.91", "volume": "3138.87841016", "low": "573.51", "ask": "584.51", "open": 576.53} </i><br />
<br />
simple parse and Graph View<br />
<code>jObj = json.loads(urllib2.urlopen("https://www.bitstamp.net/api/ticker/").read())</code><br />
<code>lastNum =int(float(jObj["last"]))</code>
and show one point... of graph.

