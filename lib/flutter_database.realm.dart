// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'flutter_database.dart';

// **************************************************************************
// RealmObjectGenerator
// **************************************************************************

// ignore_for_file: type=lint
class ROPgmRelation extends _ROPgmRelation
    with RealmEntity, RealmObjectBase, RealmObject {
  ROPgmRelation(
    String identifier,
    String belongToUid,
    String uid,
    String cfgs,
    String tag,
    String tagName,
    int type,
    int updateTime, {
    ROPgmStatus? status,
  }) {
    RealmObjectBase.set(this, 'identifier', identifier);
    RealmObjectBase.set(this, 'belongToUid', belongToUid);
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'cfgs', cfgs);
    RealmObjectBase.set(this, 'tag', tag);
    RealmObjectBase.set(this, 'tagName', tagName);
    RealmObjectBase.set(this, 'type', type);
    RealmObjectBase.set(this, 'status', status);
    RealmObjectBase.set(this, 'updateTime', updateTime);
  }

  ROPgmRelation._();

  @override
  String get identifier =>
      RealmObjectBase.get<String>(this, 'identifier') as String;
  @override
  set identifier(String value) =>
      RealmObjectBase.set(this, 'identifier', value);

  @override
  String get belongToUid =>
      RealmObjectBase.get<String>(this, 'belongToUid') as String;
  @override
  set belongToUid(String value) =>
      RealmObjectBase.set(this, 'belongToUid', value);

  @override
  String get uid => RealmObjectBase.get<String>(this, 'uid') as String;
  @override
  set uid(String value) => RealmObjectBase.set(this, 'uid', value);

  @override
  String get cfgs => RealmObjectBase.get<String>(this, 'cfgs') as String;
  @override
  set cfgs(String value) => RealmObjectBase.set(this, 'cfgs', value);

  @override
  String get tag => RealmObjectBase.get<String>(this, 'tag') as String;
  @override
  set tag(String value) => RealmObjectBase.set(this, 'tag', value);

  @override
  String get tagName => RealmObjectBase.get<String>(this, 'tagName') as String;
  @override
  set tagName(String value) => RealmObjectBase.set(this, 'tagName', value);

  @override
  int get type => RealmObjectBase.get<int>(this, 'type') as int;
  @override
  set type(int value) => RealmObjectBase.set(this, 'type', value);

  @override
  ROPgmStatus? get status =>
      RealmObjectBase.get<ROPgmStatus>(this, 'status') as ROPgmStatus?;
  @override
  set status(covariant ROPgmStatus? value) =>
      RealmObjectBase.set(this, 'status', value);

  @override
  int get updateTime => RealmObjectBase.get<int>(this, 'updateTime') as int;
  @override
  set updateTime(int value) => RealmObjectBase.set(this, 'updateTime', value);

  @override
  Stream<RealmObjectChanges<ROPgmRelation>> get changes =>
      RealmObjectBase.getChanges<ROPgmRelation>(this);

  @override
  Stream<RealmObjectChanges<ROPgmRelation>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<ROPgmRelation>(this, keyPaths);

  @override
  ROPgmRelation freeze() => RealmObjectBase.freezeObject<ROPgmRelation>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'identifier': identifier.toEJson(),
      'belongToUid': belongToUid.toEJson(),
      'uid': uid.toEJson(),
      'cfgs': cfgs.toEJson(),
      'tag': tag.toEJson(),
      'tagName': tagName.toEJson(),
      'type': type.toEJson(),
      'status': status.toEJson(),
      'updateTime': updateTime.toEJson(),
    };
  }

  static EJsonValue _toEJson(ROPgmRelation value) => value.toEJson();
  static ROPgmRelation _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'identifier': EJsonValue identifier,
        'belongToUid': EJsonValue belongToUid,
        'uid': EJsonValue uid,
        'cfgs': EJsonValue cfgs,
        'tag': EJsonValue tag,
        'tagName': EJsonValue tagName,
        'type': EJsonValue type,
        'updateTime': EJsonValue updateTime,
      } =>
        ROPgmRelation(
          fromEJson(identifier),
          fromEJson(belongToUid),
          fromEJson(uid),
          fromEJson(cfgs),
          fromEJson(tag),
          fromEJson(tagName),
          fromEJson(type),
          fromEJson(updateTime),
          status: fromEJson(ejson['status']),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(ROPgmRelation._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, ROPgmRelation, 'ROPgmRelation', [
      SchemaProperty('identifier', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('belongToUid', RealmPropertyType.string),
      SchemaProperty('uid', RealmPropertyType.string),
      SchemaProperty('cfgs', RealmPropertyType.string),
      SchemaProperty('tag', RealmPropertyType.string),
      SchemaProperty('tagName', RealmPropertyType.string),
      SchemaProperty('type', RealmPropertyType.int),
      SchemaProperty('status', RealmPropertyType.object,
          optional: true, linkTarget: 'ROPgmStatus'),
      SchemaProperty('updateTime', RealmPropertyType.int),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class ROPgmStatus extends _ROPgmStatus
    with RealmEntity, RealmObjectBase, RealmObject {
  ROPgmStatus(
    String identifier,
    String belongToUid,
    String uid,
    String status,
  ) {
    RealmObjectBase.set(this, 'identifier', identifier);
    RealmObjectBase.set(this, 'belongToUid', belongToUid);
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'status', status);
  }

  ROPgmStatus._();

  @override
  String get identifier =>
      RealmObjectBase.get<String>(this, 'identifier') as String;
  @override
  set identifier(String value) =>
      RealmObjectBase.set(this, 'identifier', value);

  @override
  String get belongToUid =>
      RealmObjectBase.get<String>(this, 'belongToUid') as String;
  @override
  set belongToUid(String value) =>
      RealmObjectBase.set(this, 'belongToUid', value);

  @override
  String get uid => RealmObjectBase.get<String>(this, 'uid') as String;
  @override
  set uid(String value) => RealmObjectBase.set(this, 'uid', value);

  @override
  String get status => RealmObjectBase.get<String>(this, 'status') as String;
  @override
  set status(String value) => RealmObjectBase.set(this, 'status', value);

  @override
  Stream<RealmObjectChanges<ROPgmStatus>> get changes =>
      RealmObjectBase.getChanges<ROPgmStatus>(this);

  @override
  Stream<RealmObjectChanges<ROPgmStatus>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<ROPgmStatus>(this, keyPaths);

  @override
  ROPgmStatus freeze() => RealmObjectBase.freezeObject<ROPgmStatus>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'identifier': identifier.toEJson(),
      'belongToUid': belongToUid.toEJson(),
      'uid': uid.toEJson(),
      'status': status.toEJson(),
    };
  }

  static EJsonValue _toEJson(ROPgmStatus value) => value.toEJson();
  static ROPgmStatus _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'identifier': EJsonValue identifier,
        'belongToUid': EJsonValue belongToUid,
        'uid': EJsonValue uid,
        'status': EJsonValue status,
      } =>
        ROPgmStatus(
          fromEJson(identifier),
          fromEJson(belongToUid),
          fromEJson(uid),
          fromEJson(status),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(ROPgmStatus._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, ROPgmStatus, 'ROPgmStatus', [
      SchemaProperty('identifier', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('belongToUid', RealmPropertyType.string),
      SchemaProperty('uid', RealmPropertyType.string),
      SchemaProperty('status', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class ROPgmProp extends _ROPgmProp
    with RealmEntity, RealmObjectBase, RealmObject {
  ROPgmProp(
    String identifier,
    String belongToUid,
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'identifier', identifier);
    RealmObjectBase.set(this, 'belongToUid', belongToUid);
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  ROPgmProp._();

  @override
  String get identifier =>
      RealmObjectBase.get<String>(this, 'identifier') as String;
  @override
  set identifier(String value) =>
      RealmObjectBase.set(this, 'identifier', value);

  @override
  String get belongToUid =>
      RealmObjectBase.get<String>(this, 'belongToUid') as String;
  @override
  set belongToUid(String value) =>
      RealmObjectBase.set(this, 'belongToUid', value);

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<ROPgmProp>> get changes =>
      RealmObjectBase.getChanges<ROPgmProp>(this);

  @override
  Stream<RealmObjectChanges<ROPgmProp>> changesFor([List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<ROPgmProp>(this, keyPaths);

  @override
  ROPgmProp freeze() => RealmObjectBase.freezeObject<ROPgmProp>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'identifier': identifier.toEJson(),
      'belongToUid': belongToUid.toEJson(),
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(ROPgmProp value) => value.toEJson();
  static ROPgmProp _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'identifier': EJsonValue identifier,
        'belongToUid': EJsonValue belongToUid,
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        ROPgmProp(
          fromEJson(identifier),
          fromEJson(belongToUid),
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(ROPgmProp._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(ObjectType.realmObject, ROPgmProp, 'ROPgmProp', [
      SchemaProperty('identifier', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('belongToUid', RealmPropertyType.string),
      SchemaProperty('key', RealmPropertyType.string),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class ROPgmPreference extends _ROPgmPreference
    with RealmEntity, RealmObjectBase, RealmObject {
  ROPgmPreference(
    String identifier,
    String belongToUid,
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'identifier', identifier);
    RealmObjectBase.set(this, 'belongToUid', belongToUid);
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  ROPgmPreference._();

  @override
  String get identifier =>
      RealmObjectBase.get<String>(this, 'identifier') as String;
  @override
  set identifier(String value) =>
      RealmObjectBase.set(this, 'identifier', value);

  @override
  String get belongToUid =>
      RealmObjectBase.get<String>(this, 'belongToUid') as String;
  @override
  set belongToUid(String value) =>
      RealmObjectBase.set(this, 'belongToUid', value);

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<ROPgmPreference>> get changes =>
      RealmObjectBase.getChanges<ROPgmPreference>(this);

  @override
  Stream<RealmObjectChanges<ROPgmPreference>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<ROPgmPreference>(this, keyPaths);

  @override
  ROPgmPreference freeze() =>
      RealmObjectBase.freezeObject<ROPgmPreference>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'identifier': identifier.toEJson(),
      'belongToUid': belongToUid.toEJson(),
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(ROPgmPreference value) => value.toEJson();
  static ROPgmPreference _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'identifier': EJsonValue identifier,
        'belongToUid': EJsonValue belongToUid,
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        ROPgmPreference(
          fromEJson(identifier),
          fromEJson(belongToUid),
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(ROPgmPreference._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, ROPgmPreference, 'ROPgmPreference', [
      SchemaProperty('identifier', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('belongToUid', RealmPropertyType.string),
      SchemaProperty('key', RealmPropertyType.string),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class ROProp extends _ROProp with RealmEntity, RealmObjectBase, RealmObject {
  ROProp(
    String identifier,
    String belongToUid,
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'identifier', identifier);
    RealmObjectBase.set(this, 'belongToUid', belongToUid);
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  ROProp._();

  @override
  String get identifier =>
      RealmObjectBase.get<String>(this, 'identifier') as String;
  @override
  set identifier(String value) =>
      RealmObjectBase.set(this, 'identifier', value);

  @override
  String get belongToUid =>
      RealmObjectBase.get<String>(this, 'belongToUid') as String;
  @override
  set belongToUid(String value) =>
      RealmObjectBase.set(this, 'belongToUid', value);

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<ROProp>> get changes =>
      RealmObjectBase.getChanges<ROProp>(this);

  @override
  Stream<RealmObjectChanges<ROProp>> changesFor([List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<ROProp>(this, keyPaths);

  @override
  ROProp freeze() => RealmObjectBase.freezeObject<ROProp>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'identifier': identifier.toEJson(),
      'belongToUid': belongToUid.toEJson(),
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(ROProp value) => value.toEJson();
  static ROProp _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'identifier': EJsonValue identifier,
        'belongToUid': EJsonValue belongToUid,
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        ROProp(
          fromEJson(identifier),
          fromEJson(belongToUid),
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(ROProp._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(ObjectType.realmObject, ROProp, 'ROProp', [
      SchemaProperty('identifier', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('belongToUid', RealmPropertyType.string),
      SchemaProperty('key', RealmPropertyType.string),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class ROPreference extends _ROPreference
    with RealmEntity, RealmObjectBase, RealmObject {
  ROPreference(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  ROPreference._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<ROPreference>> get changes =>
      RealmObjectBase.getChanges<ROPreference>(this);

  @override
  Stream<RealmObjectChanges<ROPreference>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<ROPreference>(this, keyPaths);

  @override
  ROPreference freeze() => RealmObjectBase.freezeObject<ROPreference>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(ROPreference value) => value.toEJson();
  static ROPreference _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        ROPreference(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(ROPreference._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, ROPreference, 'ROPreference', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}
