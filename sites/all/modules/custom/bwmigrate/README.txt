
This is the BW Migrate module.


== Set up the BW Rox database

cd ~/playground
# If needed: fetch BW Rox
git clone rox...
cd testdb; unzip bewelcome_db*.sql.zip
mysqladmin create bwroxdb
# use the same user that has privileges to BW Drupal database
mysql -e 'GRANT ALL PRIVILEGES ON bwroxdb.* TO bwdrupaluser@localhost
cat bewelcome_db*sql | mysql bwroxdb
