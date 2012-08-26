<?php


class bw_migrate_Migration_comment_groupDiscussion extends bw_migrate_Migration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Group discussion comments';

    $dest->comment('group_discussion');
    $src->primary('postid');

    $q = $src->rox_select('forums_posts', 'p');
    $q->fields('p', array(
      'id', 'postid',
      'threadid',
      'PostVisibility', 'authorid', 'IdWriter', 'create_time', 'message',
      'IdContent', 'OwnerCanStillEdit', 'last_edittime', 'last_editorid',
      'edit_count', 'IdFirstLanguageUsed', 'HasVotes', 'IdLocalVolMessage',
      'IdLocalEvent', 'IdPoll', 'PostDeleted',
    ));
    $q->innerJoin('forums_threads', 't', 'p.threadid = t.id');
    // Require threads to be in a group.
    // Otherwise, we make them a different content type. Do we?
    $q->innerJoin('groups', 'g', 't.IdGroup = g.id');
    $q->groupBy('p.postid');

    $map->map('comment_body', 'message');
    $map->defaultValue('comment_format', 'filtered_html');

    $map->uid('uid', 'idwriter');
    $map->foreignKey('nid', 'threadid', 'node_group_discussion');

    $map->strtotime('created', 'create_time');
    $map->strtotime('changed', 'last_edittime');

    $src->ignore(array(
      'id',  // identical with postid, it looks like.
      'postvisibility',
      'authorid',  // seems broken. use idwriter instead.
      'idcontent',  // no idea what that is
      'ownercanstilledit',  // we allow that forever now?
      'last_editorid',
      'edit_count',
      'idfirstlanguageused',
      'hasvotes',
      'idlocalvolmessage',
      'idlocalevent',
      'idpoll',
      'postdeleted',
    ));
    $dest->ignore(array(
      'pid',  // "parent" comment, for threaded view. Does not exist in rox.
      'subject',  // replies in rox forum don't have a subject.
      'status',
      'thread',  // what is this?

      'language',
      'path',

      // These fields are meant for blog commenting from ppl w/o account.
      'name', 'hostname', 'mail', 'homepage',
    ));
  }
}


