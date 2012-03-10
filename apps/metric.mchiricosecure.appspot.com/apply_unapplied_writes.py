#!/usr/bin/python2.4
#
# Copyright 2010 Google Inc.

"""Methods to fix unapplied writes.

Unapplied writes are stored in the datastore as entities where the
child node of the entity key has kind __unapplied_write__OriginalKind.

This module contains methods for applying those writes.

Currently it contains methods which work at the datastore low level API.

Sample usage using remote_api:
  * Enable remote_api for your application 
    (see http://code.google.com/appengine/articles/remote_api.html )
  * Change to a directory where this module exists.
  * Run remote_api_shell.py $YOURAPPID
  * In the remote_api_shell, run the following:
    import apply_unapplied_writes
    apply_unapplied_writes.apply_entity_by_name(YOURKIND, A KEY NAME OR ID)


Sample usage using the map reduce framework:
  * Install the map reduce framework in your app.
    (see http://code.google.com/p/appengine-mapreduce/ )
  * Add this module to your app.
  * Add the following to the mapreduce.yaml file:
      mapreduce:
      - name: "Apply unapplied writes"
        mapper:
          input_reader: mapreduce.input_readers.DatastoreInputReader
          handler: apply_unapplied_writes.apply_model_instance
          params:
          - name: entity_kind
  * Visit http://YOURAPP.appspot.com/mapreduce/ ,
  * Select 'Unapplied Entity Map' from the dropdown.
  * Enter the kind you wish to apply.
  * Click Launch Job.
"""

import logging
from google.appengine.api import datastore


UNAPPLIED_WRITE_KIND_PREFIX = '__unapplied_write__'
UNAPPLIED_WRITE_KIND_PREFIX_LEN = len(UNAPPLIED_WRITE_KIND_PREFIX)


def apply_entity(unapplied_entity, delete_unapplied_entity=True):
  """Re-write an entity representing an unapplied write  to apply it.

  Args:
    entity: An app engine datastore entity, typically loaded by datastore.Get.
      This will not work for a model instance, e.g. one loaded from db.get.
    delete_unapplied_entity: If true, the record of the unapplied write will
        be removed from the datastore.
  """
  key = unapplied_entity.key()
  path = unapplied_entity.key().to_path()
  kind = path[-2]
  if not kind.startswith(UNAPPLIED_WRITE_KIND_PREFIX):
    logging.Error("Attempting to apply an already applied write: %r", key)
    return
  kind = kind[UNAPPLIED_WRITE_KIND_PREFIX_LEN:]
  id_or_name = path[-1]
  namespace = unapplied_entity.namespace()

  # You can insert code here to change id_or_name.

  if isinstance(id_or_name, basestring):
    entity_to_apply = datastore.Entity(kind, key.parent(), name=id_or_name,
                                      namespace=namespace)
  elif id_or_name:
    entity_to_apply = datastore.Entity(kind, key.parent(), id=id_or_name,
                                       namespace=namespace)
  else:
    entity_to_apply = datastore.Entity(kind, key.parent(),
                                       namespace=namespace)
  entity_to_apply.update(unapplied_entity)

  # You can insert code here to change entity_to_apply.

  datastore.Put(entity_to_apply)
  if delete_unapplied_entity:
    datastore.Delete(unapplied_entity)


def apply_entity_by_name(kind, id_or_name, parent=None,
                         delete_unapplied_entity=True):
  """Apply an unapplied write for a given kind and id or name.

  This will load and apply an unapplied write for the identified
  entity.

  Args:
    kind: The kind of the entity to apply.
    id_or_name: The numeric ID or string name of the entity to find and apply.
    parent: Parent key for the entity to apply.
    delete_unapplied_entity: If true, the record of the unapplied write will
        be removed from the datastore.
  """

  if parent:
    path = parent.to_path()
  else:
    path = []
  path += [UNAPPLIED_WRITE_KIND_PREFIX + kind, id_or_name]
  key = datastore.Key.from_path(*path)
  unapplied_entity = datastore.Get(key)
  apply_entity(unapplied_entity, delete_unapplied_entity)


def apply_model_instance(model_instance, delete_unapplied_entity=True):
  """Apply an unapplied write from a model instance.

  This is a wrapper for apply_entity, suitable for use with the
  App Engine mapper framework.

  Args:
   model_instance. This is typically the result of a db.get or db.Query.get.
   delete_unapplied_entity: If true, the record of the unapplied write will
        be removed from the datastore.
  """
  unapplied_entity = model_instance._populate_entity()
  apply_entity(unapplied_entity, delete_unapplied_entity)

