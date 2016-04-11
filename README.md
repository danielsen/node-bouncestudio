node-bouncestudio provdides a NodeJS module ('bouncestudio') for interacting
with the [BoogieTools BounceStudio](http://www.boogietools.com/Products/Linux/)
API.

### Overview
The `bouncestudio` modules provides access to all functions of the 
[BoogieTools BounceStudio](http://www.boogietools.com/Products/Linux/) API. For
more information, please consult the [BounceStudio Documentation](http://www.boogietools.com/Products/Linux/BounceStudioAPI/help/help.html) or use Doxygen to
build documentation locally. Please keep in mind that while this module is
provided under an open-source license, 
[BounceStudio](http://www.boogietools.com/Products/Linux/) is not open-source 
and requires a license key to be used.

### Prerequisites
* [NodeJS v0.10+](http://www.nodejs.org)
* npm - Usually packaged with NodeJS
* [BoogieTools BounceStudio](http://www.boogietools.com/Products/Linux/) API
* BounceStudio API key

### Installation
    npm install danielsen/node-bouncestudio

or

    # cd /path/to/myapp/node_modules
    # mkdir bouncestudio
    # cd bouncestudio
    # git clone git@github.com:danielsen/node-bouncestudio.git
    # npm install

### Documentation
The best documentation is the [BounceStudio Documentation](http://www.boogietools.com/Products/Linux/BounceStudioAPI/help/help.html). This module implements all
the functions described in the documentation. All function names remain the 
same. Local documentation can be generated with the `doxygen` command.

    # doxygen Doxyfile

### Usage
Function names are not modified. They are the same as noted in the 
documentation. The primary function is `bsBounceCheck` which will return an
object including the numeric bounce type and verbose description as defined 
[here](http://www.boogietools.com/Products/Linux/BounceStudioAPI/help/help.html)
, and the bounced email address.

    var fs   = require('fs');
    var btbs = require('bouncestudio');

    var key     = 'Your API KEY here';
    var rawDsn  = fs.readFileSync('path/to/dsn.eml', 'utf8').toString();
    console.log(btbs.bsCheckBounce(rawDsn, "", key);
