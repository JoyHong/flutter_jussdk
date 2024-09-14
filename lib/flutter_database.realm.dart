// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'flutter_database.dart';

// **************************************************************************
// RealmObjectGenerator
// **************************************************************************

// ignore_for_file: type=lint
class JusPgmUserRelation extends _JusPgmUserRelation
    with RealmEntity, RealmObjectBase, RealmObject {
  JusPgmUserRelation(
    String uid,
    String cfgs,
    String tag,
    String tagName,
    int type,
    int updateTime, {
    JusPgmStatus? status,
  }) {
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'cfgs', cfgs);
    RealmObjectBase.set(this, 'tag', tag);
    RealmObjectBase.set(this, 'tagName', tagName);
    RealmObjectBase.set(this, 'type', type);
    RealmObjectBase.set(this, 'status', status);
    RealmObjectBase.set(this, 'updateTime', updateTime);
  }

  JusPgmUserRelation._();

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
  JusPgmStatus? get status =>
      RealmObjectBase.get<JusPgmStatus>(this, 'status') as JusPgmStatus?;
  @override
  set status(covariant JusPgmStatus? value) =>
      RealmObjectBase.set(this, 'status', value);

  @override
  int get updateTime => RealmObjectBase.get<int>(this, 'updateTime') as int;
  @override
  set updateTime(int value) => RealmObjectBase.set(this, 'updateTime', value);

  @override
  Stream<RealmObjectChanges<JusPgmUserRelation>> get changes =>
      RealmObjectBase.getChanges<JusPgmUserRelation>(this);

  @override
  Stream<RealmObjectChanges<JusPgmUserRelation>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusPgmUserRelation>(this, keyPaths);

  @override
  JusPgmUserRelation freeze() =>
      RealmObjectBase.freezeObject<JusPgmUserRelation>(this);

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

  static EJsonValue _toEJson(JusPgmUserRelation value) => value.toEJson();
  static JusPgmUserRelation _fromEJson(EJsonValue ejson) {
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
        JusPgmUserRelation(
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
    RealmObjectBase.registerFactory(JusPgmUserRelation._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusPgmUserRelation, 'JusPgmUserRelation', [
      SchemaProperty('uid', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('cfgs', RealmPropertyType.string),
      SchemaProperty('tag', RealmPropertyType.string),
      SchemaProperty('tagName', RealmPropertyType.string),
      SchemaProperty('type', RealmPropertyType.int),
      SchemaProperty('status', RealmPropertyType.object,
          optional: true, linkTarget: 'JusPgmStatus'),
      SchemaProperty('updateTime', RealmPropertyType.int),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusPgmStatus extends _JusPgmStatus
    with RealmEntity, RealmObjectBase, RealmObject {
  JusPgmStatus(
    String uid,
    String status,
  ) {
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'status', status);
  }

  JusPgmStatus._();

  @override
  String get uid => RealmObjectBase.get<String>(this, 'uid') as String;
  @override
  set uid(String value) => RealmObjectBase.set(this, 'uid', value);

  @override
  String get status => RealmObjectBase.get<String>(this, 'status') as String;
  @override
  set status(String value) => RealmObjectBase.set(this, 'status', value);

  @override
  Stream<RealmObjectChanges<JusPgmStatus>> get changes =>
      RealmObjectBase.getChanges<JusPgmStatus>(this);

  @override
  Stream<RealmObjectChanges<JusPgmStatus>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusPgmStatus>(this, keyPaths);

  @override
  JusPgmStatus freeze() => RealmObjectBase.freezeObject<JusPgmStatus>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'uid': uid.toEJson(),
      'status': status.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusPgmStatus value) => value.toEJson();
  static JusPgmStatus _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'uid': EJsonValue uid,
        'status': EJsonValue status,
      } =>
        JusPgmStatus(
          fromEJson(uid),
          fromEJson(status),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusPgmStatus._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusPgmStatus, 'JusPgmStatus', [
      SchemaProperty('uid', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('status', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusPgmUserProp extends _JusPgmUserProp
    with RealmEntity, RealmObjectBase, RealmObject {
  JusPgmUserProp(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  JusPgmUserProp._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<JusPgmUserProp>> get changes =>
      RealmObjectBase.getChanges<JusPgmUserProp>(this);

  @override
  Stream<RealmObjectChanges<JusPgmUserProp>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusPgmUserProp>(this, keyPaths);

  @override
  JusPgmUserProp freeze() => RealmObjectBase.freezeObject<JusPgmUserProp>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusPgmUserProp value) => value.toEJson();
  static JusPgmUserProp _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        JusPgmUserProp(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusPgmUserProp._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, JusPgmUserProp, 'JusPgmUserProp', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class JusPgmUserPendingProp extends _JusPgmUserPendingProp
    with RealmEntity, RealmObjectBase, RealmObject {
  JusPgmUserPendingProp(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  JusPgmUserPendingProp._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<JusPgmUserPendingProp>> get changes =>
      RealmObjectBase.getChanges<JusPgmUserPendingProp>(this);

  @override
  Stream<RealmObjectChanges<JusPgmUserPendingProp>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<JusPgmUserPendingProp>(this, keyPaths);

  @override
  JusPgmUserPendingProp freeze() =>
      RealmObjectBase.freezeObject<JusPgmUserPendingProp>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(JusPgmUserPendingProp value) => value.toEJson();
  static JusPgmUserPendingProp _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        JusPgmUserPendingProp(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(JusPgmUserPendingProp._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(ObjectType.realmObject, JusPgmUserPendingProp,
        'JusPgmUserPendingProp', [
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
