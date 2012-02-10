tip for increasing marker positioning accuracy.
after getlocations_fields has been installed, using phpmyadmin or similar,
change the latitude and longitude fields by setting the size to '10,6'

Views for Getlocations Fields

Name: Getlocations
Description: Provides a block with a link to a map.
This view should work out of the box.


Name: Getlocations map
Description: Provides a map of a locations_fields enabled node.

Configure contextual filter: Content: Nid
Specify validation criteria
Choose the content type


Name: Getlocations map allnodes
Description: Provides a map of all locations_fields enabled nodes.


Name: Getlocations map nearby
Description: Provides a map of all nearby locations_fields enabled nodes.

To get this to work you will need to do some configuring:
Configure contextual filter: Content: Nid
Specify validation criteria
Choose the content type

Configure filter criterion: Getlocations Fields: Distance
Make sure it is pointing to the right Location to use. You can also set the default Operator, Units and Distance.

Configure extra settings for sort criterion Getlocations Fields: Distance
Make sure it is pointing to the right Location to use.

In Block 5 you will want to do the Format > Getlocations > Settings
Exposing forms in blocks with maps does NOT work at present.

In Block 6 there is no further configuration required.
You might want to try exposing the Pager, Distance or Order. Remember to set ajax to Yes


Name: Getlocations show all
Description: Provides a map of all locations_fields enabled content types.


Name: Getlocations map allusers
Description: Provides a map of all locations_fields enabled users.


Name: Getlocations User
Description: Provides a link to a map of a locations_fields enabled user.
This view should work out of the box.


Name: Getlocations map nearby users
Description: Provides a map of all nearby locations_fields enabled users.

To get this to work you will need to do some configuring:

Configure contextual filter: User: Uid
Specify validation criteria

Configure filter criterion: Getlocations Fields: Distance
Make sure it is pointing to the right Location to use. You can also set the default Operator, Units and Distance.

Configure extra settings for sort criterion Getlocations Fields: Distance
Make sure it is pointing to the right Location to use.

