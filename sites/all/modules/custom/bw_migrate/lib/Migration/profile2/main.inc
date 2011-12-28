<?php


/**
 * Migration class to import BW members
 */
class bw_migrate_Migration_profile2_main extends bw_migrate_Migration {

  public function _init($src, $dest, $map) {

    $this->description = t('Migration of BW Rox members table into profile2 entities');

    $dest->dest('Profile2', 'main');
    $src->primary('id');

    $q = $src->rox_select('members', 'm');
    $q->innerJoin('user', 'u', 'u.handle = m.Username');
    $q->groupBy('m.id');
    $q->fields('m', array(
      'id', 'Username',
      'FirstName', 'SecondName', 'LastName', 'Occupation', 'ProfileSummary',
      'Gender', 'BirthDate', 'WebSite', 'Books', 'Music', 'Movies', 'Hobbies',
      'ILiveWith', 'InformationToGuest', 'TypicOffer',
    ));
    $q->fields('u', array(
      
    ));
    $q->leftJoin('addresses', 'a', 'm.id = a.IdMember');
    $q->fields('a', array('HouseNumber', 'StreetName', 'Zip', 'IdCity'));
    $q->leftJoin('membersphotos', 'p', 'm.id = p.IdMember');
    $q->fields('p', array('FilePath'));

    $map->uid('uid', 'id');
    $map->uid('revision_uid', 'id');

    $map->crypted('field_firstname', 'firstname');
    $map->crypted('field_secondname', 'secondname');
    $map->crypted('field_lastname', 'lastname');
    $map->crypted('field_profile_summary', 'profilesummary');
    $map->crypted('field_occupation', 'occupation');

    $map->crypted('field_books', 'books');
    $map->crypted('field_music', 'music');
    $map->crypted('field_films', 'movies');
    $map->crypted('field_hobbies', 'hobbies');
    $map->crypted('field_i_live_with', 'ilivewith');
    // $map->crypted('
    $map->crypted('field_housenumber', 'housenumber');
    $map->crypted('field_street', 'streetname');
    $map->crypted('field_zipcode', 'zip');

    $map->map('field_gender', 'gender');
    $map->map('field_birth_date', 'birthdate');
    $map->map('field_website', 'website');

    // $map->map('field_photos', 'filepath');

    // Unmapped fields
    $src->ignore(array(
      'username', 'idcity', 'typicoffer', 'informationtoguest',
      'filepath',
    ));
    $dest->ignore(array(
      'language', 'field_im', 'field_max_length_of_stay',
      'field_max_number_of_guests', 'field_organisations_i_belong_to',
      'field_phone_home', 'path',
      'field_photos',
    ));
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
}




