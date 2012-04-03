The Getlocations_blocks module provides some blocks with a form to help search
the Getlocations_fields table. It works in conjunction with the following views:

Getlocations by city

Getlocations by province

Getlocations by postcode

Getlocations by country

A good way to work with these is to enable the view, clone it
and then disable the original. You can then set up the clone to your liking.

Once the view is set up you can configure the relevant block.
You can use either a Dropdown or an Autocomplete.
The Dropdown makes the most sense where there are only a few choices, eg less than 50

If you changed the path to the page in the view you will need to set this
in the block as well.

Each form is fully themed so you can alter it using the usual theming methods.
Each block is wrapped in a div which you can control with css.
