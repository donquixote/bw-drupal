<?php


class BWUserMigration extends BWMigration {

  protected function _init($src, $dest, $map) {

    $this->description = 'BW users';

    $dest->entity('user');

    $src->id('User ID.');
    $q = $src->rox_select('members', 'm');
    $q->leftJoin('user', 'u', 'u.handle = m.Username');
    $q->fields('m', array('id', 'Username'));
    $q->fields('u', array('email', 'pw', 'active', 'lastlogin'));

    // Dedupe assures that value is unique. Use it when source data is non-unique.
    // Pass the Drupal table and column for determining uniqueness.
    $map->map('name', 'Username')->dedupe('users', 'name');

    $map->map('field_bw_rox_username', 'Username');

    // Here we have a special case - we want to transform a date/time string
    // into a UNIX timestamp, and also apply a specific timezone. The
    // mapping of posted to created here is primarily for the sake of
    // documentation - the prepare method below actually populates the field.
    $map->map('login', 'lastlogin');
    $map->map('access', 'lastlogin');

    $map->map('mail', 'email');
    $map->map('pass', 'pw');  // TODO: like D6->7 migration

    // Instead of mapping a source field to a destination field, you can
    // hardcode a default value. You can also use both together - if a default
    // value is provided in addition to a source field, the default value will
    // be applied to any rows where the source field is empty or NULL.
    $map->map('roles')->defaultValue(drupal_map_assoc(array(2)));
    // $map->map('field_migrate_example_gender', 'sex');

    // TODO: fix
    //    $map->map('active', 'status');
    $map->map('status')->defaultValue(1); // 1 => active

    // Unmapped source fields
    $map->map(NULL, 'nickname')->issueGroup(t('DNM'));

    // Unmapped destination fields
    $map->map('theme')->issueGroup(t('DNM'));
    $map->map('signature')->issueGroup(t('DNM'));
    $map->map('timezone')->issueGroup(t('DNM'));
    $map->map('language')->issueGroup(t('DNM'));
    $map->map('picture')->issueGroup(t('DNM'));
  }

  // If you define a prepare() method in your migration, it will be called
  // after the mappings have been applied and before the destination object is
  // saved. The first argument is the destination object as built up using
  // the mappings; the second argument is the raw source data.
  public function prepare(stdClass $account, stdClass $row) {
    // Source dates are in ISO format.
    // Because the mappings above have been applied, $account->created contains
    // the date/time string now - we could also pass $row->posted here.
    $account->created = strtotime($account->created);
  }
}
