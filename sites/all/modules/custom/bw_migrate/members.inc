<?php
/**
 * @file
 */


/**
 *
 */

class MembersPhotosFileCopyMigration extends BWMigration {

  public function _init($src, $dest, $map) {

    $dest->entity('file');
    $src->id('Image ID.');

    $q = $src->rox_select('membersphotos', 'p');
    $q->fields('p', array('id', 'FilePath'));

    $map->map('uri', 'uri');
    $map->map('filename', 'filename');
    $map->map('path', 'filename');
    $map->map('scheduler', 'publish_on');
  }

  public function prepareRow($current_row) {
    // var_dump($_SERVER['SCRIPT_FILENAME']);
    $orig = str_replace('tmp/', '', $current_row->filepath);
    $source = '' . $orig;
    $clean_name = $this->cleanPath($orig);
    $dest = 'public://' . basename($clean_name);
    $current_row->uri = $clean_name;
    var_dump($source);
    var_dump($dest);
    file_unmanaged_copy ($source, $dest);
  }

}




/**
 * Migration class to import BW members
 */
class BWMembersMigration extends BWMigration {

  public function _init($src, $dest, $map) {

    $this->description = t('Migration of BW Rox members table into profile2 entities');
    // $this->dependencies = array('BWUser');  // Add when BWUser more stable

    $dest->entity('Profile2', 'main');
    $src->id('MemberID');

    $q = $src->rox_select('members', 'm');
    $q->fields('m', array(
      'id', 'Username', 'FirstName', 'SecondName', 'LastName', 'Occupation',
      'ProfileSummary', 'Gender', 'BirthDate', 'WebSite', 'Books', 'Music',
      'Movies'
    ));
    $q->leftJoin('addresses', 'a', 'm.id = a.IdMember');
    $q->fields('a', array('HouseNumber', 'StreetName', 'Zip', 'IdCity'));
    $q->leftJoin('membersphotos', 'p', 'm.id = p.IdMember');
    $q->fields('p', array('FilePath'));

    $map->map('field_firstname', 'firstname');
    $map->map('field_secondname', 'secondname');
    $map->map('field_lastname', 'lastname');
    $map->map('field_occupation', 'occupation');

    $map->map('field_housenumber', 'housenumber');
    $map->map('field_street', 'streetname');
    $map->map('field_zipcode', 'zip');

    $map->map('field_profile_summary', 'profilesummary');
    $map->map('field_gender', 'gender');
    $map->map('field_birth_date', 'birthdate');
    $map->map('field_website', 'website');
    $map->map('field_books', 'books');
    $map->map('field_music', 'music');
    $map->map('field_movies', 'movies');

    $map->map('field_photos', 'filepath');


    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('id'));
  }

  public function prepare(stdClass $account, stdClass $row) {
    $result = db_query(
      'SELECT uid FROM {users} WHERE name = :name',
      array(':name' => $row->username)
    );
    $uid = NULL;
    // this shouldn't be a loop but just want working code now
    foreach ($result as $r) {
      $uid = $r->uid;
    }
    $account->uid = (int)$uid;
  }

  public function prepareRow($currentRow) {
    foreach (array(
      // All these columns are 'crypted' in the rox db.
      'firstname', 'secondname', 'lastname', 'profilesummary', 'occupation', 
      'books', 'music', 'movies', 'housenumber', 'streetname', 'zip',
    ) as $cf) {
      $result = $this->roxdb_connection->query(
        'SELECT MemberCryptedValue FROM {cryptedfields} WHERE id = :id',
        array(':id' => $currentRow->$cf)
      );
      // this shouldn't be a loop but just want working code now
      foreach ($result as $r) {
        $crypted = $r->membercryptedvalue;
      }
      $currentRow->$cf = preg_replace('/\<\/?membercrypted\>/', '', $crypted);
    }
  }
}


