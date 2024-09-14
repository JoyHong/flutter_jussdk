// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'flutter_database.dart';

// **************************************************************************
// RealmObjectGenerator
// **************************************************************************

// ignore_for_file: type=lint
class JusUserRelation extends _JusUserRelation
    with RealmEntity, RealmObjectBase, RealmObject {
  JusUserRelation(
    String uid,
    String cfgs,
    String tag,
    String tagName,
    int type,
    int updateTime, {
    JusStatus? status,
  }) {
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'cfgs', cfgs);
    RealmObjectBase.set(this, 'tag', tag);
    RealmObjectBase.set(this, 'tagName', tagName);
    RealmObjectBase.set(this, 'type', type);
    RealmObjectBase.set(this, 'status', status);
    RealmObjectBase.set(this, 'updateTime', updateTime);
  }

  JusUserRelation._();

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
  JusStatus? get status =>
      RealmObjectBase.get<JusStatus>(this, 'status') as JusStatus?;
  @override
  set status(covariant JusStatus? value) =>
      RealmObjectBase.set(this, 'status', value);

  @override
  int get updateTime => RealmObjectBase.get<int>(this, 'updateTime') as int;
  @override
  set updateTime(int value) => RealmObjectBase.set(this, 'updateTime', value);

  @override
  Stream<RealmObjectChanges<JusUserRelation>> get changes =>
      RealmObjectBase.getChanges<JusUserRelation>(this);

  @override
  Stream<RealmObjectChanges<JusUserRelation>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusUserRelation>(this, keyPaths);

  @override
  JusUserRelation freeze() =>
      RealmObjectBase.freezeObject<JusUserRelation>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'uid': uid.toEJson(),
      'cfgs': cfgs.toEJson(),
      'tag': tag.toEJson(),
      'tagName': tagName.toEJson(),
      'type': type.toEJson(),
      'status': status.toEJson(),
      'updateTime': updateTime.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusUserRelation value) => value.toEJson();
  static JusUserRelation _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'uid': EJsonValue uid,
        'cfgs': EJsonValue cfgs,
        'tag': EJsonValue tag,
        'tagName': EJsonValue tagName,
        'type': EJsonValue type,
        'updateTime': EJsonValue updateTime,
      } =>
        JusUserRelation(
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
    RealmObjectBase.registerFactory(JusUserRelation._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusUserRelation, 'JusUserRelation', [
      SchemaProperty('uid', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('cfgs', RealmPropertyType.string),
      SchemaProperty('tag', RealmPropertyType.string),
      SchemaProperty('tagName', RealmPropertyType.string),
      SchemaProperty('type', RealmPropertyType.int),
      SchemaProperty('status', RealmPropertyType.object,
          optional: true, linkTarget: 'JusStatus'),
      SchemaProperty('updateTime', RealmPropertyType.int),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusStatus extends _JusStatus
    with RealmEntity, RealmObjectBase, RealmObject {
  JusStatus(
    String uid,
    String status,
  ) {
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'status', status);
  }

  JusStatus._();

  @override
  String get uid => RealmObjectBase.get<String>(this, 'uid') as String;
  @override
  set uid(String value) => RealmObjectBase.set(this, 'uid', value);

  @override
  String get status => RealmObjectBase.get<String>(this, 'status') as String;
  @override
  set status(String value) => RealmObjectBase.set(this, 'status', value);

  @override
  Stream<RealmObjectChanges<JusStatus>> get changes =>
      RealmObjectBase.getChanges<JusStatus>(this);

  @override
  Stream<RealmObjectChanges<JusStatus>> changesFor([List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusStatus>(this, keyPaths);

  @override
  JusStatus freeze() => RealmObjectBase.freezeObject<JusStatus>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'uid': uid.toEJson(),
      'status': status.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusStatus value) => value.toEJson();
  static JusStatus _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'uid': EJsonValue uid,
        'status': EJsonValue status,
      } =>
        JusStatus(
          fromEJson(uid),
          fromEJson(status),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusStatus._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(ObjectType.realmObject, JusStatus, 'JusStatus', [
      SchemaProperty('uid', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('status', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusUserProp extends _JusUserProp
    with RealmEntity, RealmObjectBase, RealmObject {
  JusUserProp(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  JusUserProp._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<JusUserProp>> get changes =>
      RealmObjectBase.getChanges<JusUserProp>(this);

  @override
  Stream<RealmObjectChanges<JusUserProp>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusUserProp>(this, keyPaths);

  @override
  JusUserProp freeze() => RealmObjectBase.freezeObject<JusUserProp>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusUserProp value) => value.toEJson();
  static JusUserProp _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        JusUserProp(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusUserProp._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusUserProp, 'JusUserProp', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusUserPendingProp extends _JusUserPendingProp
    with RealmEntity, RealmObjectBase, RealmObject {
  JusUserPendingProp(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  JusUserPendingProp._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<JusUserPendingProp>> get changes =>
      RealmObjectBase.getChanges<JusUserPendingProp>(this);

  @override
  Stream<RealmObjectChanges<JusUserPendingProp>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusUserPendingProp>(this, keyPaths);

  @override
  JusUserPendingProp freeze() =>
      RealmObjectBase.freezeObject<JusUserPendingProp>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusUserPendingProp value) => value.toEJson();
  static JusUserPendingProp _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        JusUserPendingProp(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusUserPendingProp._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusUserPendingProp, 'JusUserPendingProp', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusPreference extends _JusPreference
    with RealmEntity, RealmObjectBase, RealmObject {
  JusPreference(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  JusPreference._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<JusPreference>> get changes =>
      RealmObjectBase.getChanges<JusPreference>(this);

  @override
  Stream<RealmObjectChanges<JusPreference>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusPreference>(this, keyPaths);

  @override
  JusPreference freeze() => RealmObjectBase.freezeObject<JusPreference>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusPreference value) => value.toEJson();
  static JusPreference _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        JusPreference(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusPreference._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusPreference, 'JusPreference', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}
