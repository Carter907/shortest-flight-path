### Shortest Flight Path

**Data**

This program uses data from the [Bureau of Transportation Statistics](https://www.transtats.bts.gov/DL_SelectFields.aspx?QO_fu146_anzr=b0-gvzr&gnoyr_VQ=FGJ) and is contained in the [cvs file](https://github.com/Carter907/shortest-flight-path/blob/main/FlightConnectionsJan2025.csv) at the project root.

### Program
A basic CLI application that expects source and destination airports in the official, alpha-numeric code, and outputs the shortest distance in miles.

**Usage**

```sh
flightpath --src SUN --dest LAX
```
output:
```sh
The shortest path from SUN to LAX is [insert route found], with a total distance of [insert total distance of path] miles.
```
