<?php


abstract class bw_migrate_Migration_file_membersphotos extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $dest->dest('file');
    $src->primary('id');

    $q = $src->rox_select('membersphotos', 'p');
    $q->fields('p', array('id', 'FilePath'));

    $map->map('uri', 'uri');
    $map->map('filename', 'filename');
    $map->map('path', 'filename');
    $map->map('scheduler', 'publish_on');
  }

  protected function _prepareRow($current_row) {
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
