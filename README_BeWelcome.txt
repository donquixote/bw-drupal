
This repository contains the BeWelcome Drupal setup.  You can set it
up like a normal Drupal 7 installation, by default it will have
selected the BeWelcome profile.

You will have to create sites/default/files with proper permissions
(chmod 777) and you'll have to copy sites/default/default.settings.php
to sites/default/settings.php


After installation you will have to
- enable the bewelcome main module in admin/modules
- enable the theme in admin/appearance/list

This will happen automatically in the future via bewelcome.profile.

== Test database
- find it here: https://gitorious.org/bewelcome/rox/trees/master/testdb
