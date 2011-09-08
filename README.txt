for Drupal 7
Getlocations will provide a Google maps API version 3 enabled map on which to
display markers of locations found in location-enabled content-types.

INSTALL
Before installing getlocations please ensure that you have location and
libraries modules installed

The getlocations folder contains a folder 'library' which contains
getlocation-markers.tar.gz
This tarball needs to be unpacked into your libraries folder, so
you have a path something like this:
sites/all/libraries/getlocations/markers

There is also getlocations-markers-extra.tar.gz which contains
numbered and letter markers. You can optionally add these if you need them.

CONFIGURE
You should configure Getlocations by visiting admin/config/services/getlocations.

USAGE
Getlocations maps can be displayed per node, eg "/getlocations/node/xxx"
will display all the locations associated with that node.

They can also be displayed per content-type, so if your content-type
has a machine name 'venue' you can show them all with
"/getlocations/type/venue".

With the above path you can add another two parameters which must be a
location key/value pair, so "/getlocations/type/venue/city/london" will
give you all the locations in London. The keys might typically be

lid
name
street
additional
city
province
postal_code
country
latitude
longitude
province_name
country_name

If you need more complex things use Views.

TODO
add location-enabled user ids once location handles users properly

You can display a list of location ids with something like
"getlocations/lids/1,2,3,4"
and a list of nodes with
"getlocations/nids/1,2,3,4"

There are some Views, disabled by default.
The getlocations View will provide a block that will appear when a location
enabled node is being shown. The block contains a link to a map.
