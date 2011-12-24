<?php


class GroupMigration extends BWMigration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Groups from BW-Rox to BW-Drupal.';

    $dest->node('group');
    $src->id('Group id');

    $q = $src->rox_select('groups', 'g');
    $q->fields('g', array(
      'id', 'Name', 'Type', 'created', 'NbChilds', 'Picture', 'MoreInfo',
      'DisplayedOnProfile', 'VisiblePosts', 'IdDescription', 'IdGeoname',
      'IsLocal',
    ));

    $map->map('title', 'Name');
    $map->map('nid', 'id');
  }
}


abstract class GroupDiscussionMigration extends BWMigration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Group discussions from BW-Rox to BW-Drupal';

    $dest->node('group_discussion');

    $src->id('forum thread id');

    $q = $src->rox_select('forums_threads', 't');
    $q->fields('t', array(
      'id',
      'expiredate', 'IdTitle', 'threadid', 'title', 'first_postid',
      'last_postid', 'replies', 'views', 'geonameid', 'admincode',
      'countrycode', 'continent', 'tag1', 'tag2', 'tag3', 'tag4', 'tag5',
      'stickyvalue', 'IdFirstLanguageUsed', 'IdGroup', 'WhoCanReply',
      'ThreadDeleted', 'ThreadVisibility',
    ));
    $q->leftJoin('forums_posts', 'p', 't.id = p.threadid AND t.first_postid = p.postid');
    $q->fields('p', array(
      'message',
    ));

    $map->map('title', 'title');
    $map->map('nid', 'id');
  }
}


abstract class GroupDiscussionCommentMigration extends BWMigration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Group discussion comments';

    $dest->comment('group_discussion');
    $src->primary('postid', 'forum post id');

    $q = $src->rox_select('forums_posts', 'p');
    $q->fields('p', array(
      // in fact, these two are identical.
      // Except, postid is auto-increment.
      'id', 'postid',
      'threadid',
      'PostVisibility', 'authorid', 'IdWriter', 'create_time', 'message',
      'IdContent', 'OwnerCanStillEdit', 'last_edittime', 'last_editorid',
      'edit_count', 'IdFirstLanguageUsed', 'HasVotes', 'IdLocalVolMessage',
      'IdLocalEvent', 'IdPoll', 'PostDeleted',
    ));

    $map->map('comment', 'message');
    $map->map('cid', 'postid');
  }
}




