// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'flutter_database.dart';

// **************************************************************************
// RealmObjectGenerator
// **************************************************************************

// ignore_for_file: type=lint
class FlutterJusRelation extends _FlutterJusRelation
    with RealmEntity, RealmObjectBase, RealmObject {
  FlutterJusRelation(
    String uid,
    String cfgs,
    String tag,
    String tagName,
    int type, {
    FlutterJusStatus? status,
  }) {
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'cfgs', cfgs);
    RealmObjectBase.set(this, 'tag', tag);
    RealmObjectBase.set(this, 'tagName', tagName);
    RealmObjectBase.set(this, 'type', type);
    RealmObjectBase.set(this, 'status', status);
  }

  FlutterJusRelation._();

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
  FlutterJusStatus? get status =>
      RealmObjectBase.get<FlutterJusStatus>(this, 'status')
          as FlutterJusStatus?;
  @override
  set status(covariant FlutterJusStatus? value) =>
      RealmObjectBase.set(this, 'status', value);

  @override
  Stream<RealmObjectChanges<FlutterJusRelation>> get changes =>
      RealmObjectBase.getChanges<FlutterJusRelation>(this);

  @override
  Stream<RealmObjectChanges<FlutterJusRelation>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<FlutterJusRelation>(this, keyPaths);

  @override
  FlutterJusRelation freeze() =>
      RealmObjectBase.freezeObject<FlutterJusRelation>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'uid': uid.toEJson(),
      'cfgs': cfgs.toEJson(),
      'tag': tag.toEJson(),
      'tagName': tagName.toEJson(),
      'type': type.toEJson(),
      'status': status.toEJson(),
    };
  }

  static EJsonValue _toEJson(FlutterJusRelation value) => value.toEJson();
  static FlutterJusRelation _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'uid': EJsonValue uid,
        'cfgs': EJsonValue cfgs,
        'tag': EJsonValue tag,
        'tagName': EJsonValue tagName,
        'type': EJsonValue type,
      } =>
        FlutterJusRelation(
          fromEJson(uid),
          fromEJson(cfgs),
          fromEJson(tag),
          fromEJson(tagName),
          fromEJson(type),
          status: fromEJson(ejson['status']),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(FlutterJusRelation._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, FlutterJusRelation, 'FlutterJusRelation', [
      SchemaProperty('uid', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('cfgs', RealmPropertyType.string),
      SchemaProperty('tag', RealmPropertyType.string),
      SchemaProperty('tagName', RealmPropertyType.string),
      SchemaProperty('type', RealmPropertyType.int),
      SchemaProperty('status', RealmPropertyType.object,
          optional: true, linkTarget: 'FlutterJusStatus'),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class FlutterJusStatus extends _FlutterJusStatus
    with RealmEntity, RealmObjectBase, RealmObject {
  FlutterJusStatus(
    String uid,
    String status,
  ) {
    RealmObjectBase.set(this, 'uid', uid);
    RealmObjectBase.set(this, 'status', status);
  }

  FlutterJusStatus._();

  @override
  String get uid => RealmObjectBase.get<String>(this, 'uid') as String;
  @override
  set uid(String value) => RealmObjectBase.set(this, 'uid', value);

  @override
  String get status => RealmObjectBase.get<String>(this, 'status') as String;
  @override
  set status(String value) => RealmObjectBase.set(this, 'status', value);

  @override
  Stream<RealmObjectChanges<FlutterJusStatus>> get changes =>
      RealmObjectBase.getChanges<FlutterJusStatus>(this);

  @override
  Stream<RealmObjectChanges<FlutterJusStatus>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<FlutterJusStatus>(this, keyPaths);

  @override
  FlutterJusStatus freeze() =>
      RealmObjectBase.freezeObject<FlutterJusStatus>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'uid': uid.toEJson(),
      'status': status.toEJson(),
    };
  }

  static EJsonValue _toEJson(FlutterJusStatus value) => value.toEJson();
  static FlutterJusStatus _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'uid': EJsonValue uid,
        'status': EJsonValue status,
      } =>
        FlutterJusStatus(
          fromEJson(uid),
          fromEJson(status),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(FlutterJusStatus._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, FlutterJusStatus, 'FlutterJusStatus', [
      SchemaProperty('uid', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('status', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class FlutterJusProperty extends _FlutterJusProperty
    with RealmEntity, RealmObjectBase, RealmObject {
  FlutterJusProperty(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  FlutterJusProperty._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<FlutterJusProperty>> get changes =>
      RealmObjectBase.getChanges<FlutterJusProperty>(this);

  @override
  Stream<RealmObjectChanges<FlutterJusProperty>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<FlutterJusProperty>(this, keyPaths);

  @override
  FlutterJusProperty freeze() =>
      RealmObjectBase.freezeObject<FlutterJusProperty>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(FlutterJusProperty value) => value.toEJson();
  static FlutterJusProperty _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        FlutterJusProperty(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(FlutterJusProperty._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, FlutterJusProperty, 'FlutterJusProperty', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class FlutterJusPendingProperty extends _FlutterJusPendingProperty
    with RealmEntity, RealmObjectBase, RealmObject {
  FlutterJusPendingProperty(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  FlutterJusPendingProperty._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<FlutterJusPendingProperty>> get changes =>
      RealmObjectBase.getChanges<FlutterJusPendingProperty>(this);

  @override
  Stream<RealmObjectChanges<FlutterJusPendingProperty>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<FlutterJusPendingProperty>(this, keyPaths);

  @override
  FlutterJusPendingProperty freeze() =>
      RealmObjectBase.freezeObject<FlutterJusPendingProperty>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(FlutterJusPendingProperty value) =>
      value.toEJson();
  static FlutterJusPendingProperty _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        FlutterJusPendingProperty(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(FlutterJusPendingProperty._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(ObjectType.realmObject, FlutterJusPendingProperty,
        'FlutterJusPendingProperty', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}

class FlutterJusPreference extends _FlutterJusPreference
    with RealmEntity, RealmObjectBase, RealmObject {
  FlutterJusPreference(
    String key,
    String value,
  ) {
    RealmObjectBase.set(this, 'key', key);
    RealmObjectBase.set(this, 'value', value);
  }

  FlutterJusPreference._();

  @override
  String get key => RealmObjectBase.get<String>(this, 'key') as String;
  @override
  set key(String value) => RealmObjectBase.set(this, 'key', value);

  @override
  String get value => RealmObjectBase.get<String>(this, 'value') as String;
  @override
  set value(String value) => RealmObjectBase.set(this, 'value', value);

  @override
  Stream<RealmObjectChanges<FlutterJusPreference>> get changes =>
      RealmObjectBase.getChanges<FlutterJusPreference>(this);

  @override
  Stream<RealmObjectChanges<FlutterJusPreference>> changesFor(
          [List<String>? keyPaths]) =>
      RealmObjectBase.getChangesFor<FlutterJusPreference>(this, keyPaths);

  @override
  FlutterJusPreference freeze() =>
      RealmObjectBase.freezeObject<FlutterJusPreference>(this);

  EJsonValue toEJson() {
    return <String, dynamic>{
      'key': key.toEJson(),
      'value': value.toEJson(),
    };
  }

  static EJsonValue _toEJson(FlutterJusPreference value) => value.toEJson();
  static FlutterJusPreference _fromEJson(EJsonValue ejson) {
    if (ejson is! Map<String, dynamic>) return raiseInvalidEJson(ejson);
    return switch (ejson) {
      {
        'key': EJsonValue key,
        'value': EJsonValue value,
      } =>
        FlutterJusPreference(
          fromEJson(key),
          fromEJson(value),
        ),
      _ => raiseInvalidEJson(ejson),
    };
  }

  static final schema = () {
    RealmObjectBase.registerFactory(FlutterJusPreference._);
    register(_toEJson, _fromEJson);
    return const SchemaObject(
        ObjectType.realmObject, FlutterJusPreference, 'FlutterJusPreference', [
      SchemaProperty('key', RealmPropertyType.string, primaryKey: true),
      SchemaProperty('value', RealmPropertyType.string),
    ]);
  }();

  @override
  SchemaObject get objectSchema => RealmObjectBase.getSchema(this) ?? schema;
}
