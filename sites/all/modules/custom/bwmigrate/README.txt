
This is the BW Migrate module.  It's building upon the Migrate module.
You need to set up the BW Rox database and you will have to use drush
to play with this.


== Set up the BW Rox database

cd ~/playground

# If needed: fetch BW Rox
git clone rox...
cd testdb; unzip bewelcome_db*.sql.zip
mysqladmin create bwroxdb

# For convenience: Use the same user that has privileges to BW Drupal database
mysql -e 'GRANT ALL PRIVILEGES ON bwroxdb.* TO bwdrupaluser@localhost
cat bewelcome_db*sql | mysql bwroxdb


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
