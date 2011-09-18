
This is the BW Migrate module.  It's building upon the Migrate module.
You need to set up the BW Rox database and you will have to use drush
to play with this.


== Set up the BW Rox database

mysqladmin create bwroxdb
zcat testdb/bewelcometest.sql.gz | mysql bwroxdb

# For convenience: Use the same user that has privileges to BW Drupal database
mysql -e 'GRANT ALL PRIVILEGES ON bwroxdb.* TO bwdrupaluser@localhost'


== settings.php

Add this to your sites/default/settings.php

$databases['bwroxdb']['default'] = $databases['default']['default'];
$databases['bwroxdb']['default']['database'] = 'bwroxdb';


TODO: find a way to add this to bwmigrate.module



== drush

If you haven't used it before, do yourself a favor and get drush,
DRUpal SHell.  You can use drush to upgrade your entire Drupal
installation, fetch and enable modules and many more great things.
It's also not so hard to add drush support to modules - so many
modules have some kind of support.

Once you have enabled the bwmigrate module, run drush with arguments
to see the possibilities.

A migration development session could look like this:

# Write a new migration thing...
drush ms           # Check if it's there with migration status
drush cc all       # Clear cache
drush ms           # Now it's there
drush mi FaqTerm   # Run FAQ term migration - see if it runs
drush ms           # Did it run?   Or not?
drush mr FaqTerm   # Revert FAQ term migration


== More information 
- http://drupal.org/project/migrate
- http://www.midwesternmac.com/blogs/jeff-geerling/using-migrate-import-content
