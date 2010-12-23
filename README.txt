// $Id$

Cave Your Trolls README

CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Installation
  * Configuration
  * Usage
  

INTRODUCTION
------------
Maintainer: Daniel Braksator (http://drupal.org/user/134005)

Project page: http://drupal.org/project/cave.


INSTALLATION
------------
1. Copy cave folder to modules (usually 'sites/all/modules') directory.
2. At 'admin/build/modules' enable the cave module.


CONFIGURATION
-------------
Enable permissions at 'admin/user/permissions'.  Users with the permission 
'administer cave' will be able to use this module.


USAGE
-----
There are several ways to add users to the cave:

1) Checking "Cave this user" in a user profile.

2) Users in roles with the 'endure cave' permission and without the 
   'administer cave' permission will have their posts hidden from other users
   by default.

3) Use the Troll module to "blacklist" the user's IP addresses for cave.
   Troll is available at http://drupal.org/project/troll.

4) Using the operations on the user administration page, or with the module
   'Views Bulk Operations'. http://drupal.org/project/views_bulk_operations