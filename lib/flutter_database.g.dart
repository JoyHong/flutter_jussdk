// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'flutter_database.dart';

// ignore_for_file: type=lint
class $FlutterJusRelationTable extends FlutterJusRelation
    with TableInfo<$FlutterJusRelationTable, FlutterJusRelationData> {
  @override
  final GeneratedDatabase attachedDatabase;
  final String? _alias;
  $FlutterJusRelationTable(this.attachedDatabase, [this._alias]);
  static const VerificationMeta _uidMeta = const VerificationMeta('uid');
  @override
  late final GeneratedColumn<String> uid = GeneratedColumn<String>(
      'uid', aliasedName, false,
      type: DriftSqlType.string,
      requiredDuringInsert: true,
      defaultConstraints: GeneratedColumn.constraintIsAlways('UNIQUE'));
  static const VerificationMeta _cfgsMeta = const VerificationMeta('cfgs');
  @override
  late final GeneratedColumn<String> cfgs = GeneratedColumn<String>(
      'cfgs', aliasedName, false,
      type: DriftSqlType.string, requiredDuringInsert: true);
  static const VerificationMeta _tagMeta = const VerificationMeta('tag');
  @override
  late final GeneratedColumn<String> tag = GeneratedColumn<String>(
      'tag', aliasedName, false,
      type: DriftSqlType.string, requiredDuringInsert: true);
  static const VerificationMeta _tagNameMeta =
      const VerificationMeta('tagName');
  @override
  late final GeneratedColumn<String> tagName = GeneratedColumn<String>(
      'tag_name', aliasedName, false,
      type: DriftSqlType.string, requiredDuringInsert: true);
  static const VerificationMeta _typeMeta = const VerificationMeta('type');
  @override
  late final GeneratedColumn<int> type = GeneratedColumn<int>(
      'type', aliasedName, false,
      type: DriftSqlType.int, requiredDuringInsert: true);
  static const VerificationMeta _statusMeta = const VerificationMeta('status');
  @override
  late final GeneratedColumn<String> status = GeneratedColumn<String>(
      'status', aliasedName, false,
      type: DriftSqlType.string, requiredDuringInsert: true);
  @override
  List<GeneratedColumn> get $columns => [uid, cfgs, tag, tagName, type, status];
  @override
  String get aliasedName => _alias ?? actualTableName;
  @override
  String get actualTableName => $name;
  static const String $name = 'flutter_jus_relation';
  @override
  VerificationContext validateIntegrity(
      Insertable<FlutterJusRelationData> instance,
      {bool isInserting = false}) {
    final context = VerificationContext();
    final data = instance.toColumns(true);
    if (data.containsKey('uid')) {
      context.handle(
          _uidMeta, uid.isAcceptableOrUnknown(data['uid']!, _uidMeta));
    } else if (isInserting) {
      context.missing(_uidMeta);
    }
    if (data.containsKey('cfgs')) {
      context.handle(
          _cfgsMeta, cfgs.isAcceptableOrUnknown(data['cfgs']!, _cfgsMeta));
    } else if (isInserting) {
      context.missing(_cfgsMeta);
    }
    if (data.containsKey('tag')) {
      context.handle(
          _tagMeta, tag.isAcceptableOrUnknown(data['tag']!, _tagMeta));
    } else if (isInserting) {
      context.missing(_tagMeta);
    }
    if (data.containsKey('tag_name')) {
      context.handle(_tagNameMeta,
          tagName.isAcceptableOrUnknown(data['tag_name']!, _tagNameMeta));
    } else if (isInserting) {
      context.missing(_tagNameMeta);
    }
    if (data.containsKey('type')) {
      context.handle(
          _typeMeta, type.isAcceptableOrUnknown(data['type']!, _typeMeta));
    } else if (isInserting) {
      context.missing(_typeMeta);
    }
    if (data.containsKey('status')) {
      context.handle(_statusMeta,
          status.isAcceptableOrUnknown(data['status']!, _statusMeta));
    } else if (isInserting) {
      context.missing(_statusMeta);
    }
    return context;
  }

  @override
  Set<GeneratedColumn> get $primaryKey => {uid};
  @override
  FlutterJusRelationData map(Map<String, dynamic> data, {String? tablePrefix}) {
    final effectivePrefix = tablePrefix != null ? '$tablePrefix.' : '';
    return FlutterJusRelationData(
      uid: attachedDatabase.typeMapping
          .read(DriftSqlType.string, data['${effectivePrefix}uid'])!,
      cfgs: attachedDatabase.typeMapping
          .read(DriftSqlType.string, data['${effectivePrefix}cfgs'])!,
      tag: attachedDatabase.typeMapping
          .read(DriftSqlType.string, data['${effectivePrefix}tag'])!,
      tagName: attachedDatabase.typeMapping
          .read(DriftSqlType.string, data['${effectivePrefix}tag_name'])!,
      type: attachedDatabase.typeMapping
          .read(DriftSqlType.int, data['${effectivePrefix}type'])!,
      status: attachedDatabase.typeMapping
          .read(DriftSqlType.string, data['${effectivePrefix}status'])!,
    );
  }

  @override
  $FlutterJusRelationTable createAlias(String alias) {
    return $FlutterJusRelationTable(attachedDatabase, alias);
  }
}

class FlutterJusRelationData extends DataClass
    implements Insertable<FlutterJusRelationData> {
  final String uid;
  final String cfgs;
  final String tag;
  final String tagName;
  final int type;
  final String status;
  const FlutterJusRelationData(
      {required this.uid,
      required this.cfgs,
      required this.tag,
      required this.tagName,
      required this.type,
      required this.status});
  @override
  Map<String, Expression> toColumns(bool nullToAbsent) {
    final map = <String, Expression>{};
    map['uid'] = Variable<String>(uid);
    map['cfgs'] = Variable<String>(cfgs);
    map['tag'] = Variable<String>(tag);
    map['tag_name'] = Variable<String>(tagName);
    map['type'] = Variable<int>(type);
    map['status'] = Variable<String>(status);
    return map;
  }

  FlutterJusRelationCompanion toCompanion(bool nullToAbsent) {
    return FlutterJusRelationCompanion(
      uid: Value(uid),
      cfgs: Value(cfgs),
      tag: Value(tag),
      tagName: Value(tagName),
      type: Value(type),
      status: Value(status),
    );
  }

  factory FlutterJusRelationData.fromJson(Map<String, dynamic> json,
      {ValueSerializer? serializer}) {
    serializer ??= driftRuntimeOptions.defaultSerializer;
    return FlutterJusRelationData(
      uid: serializer.fromJson<String>(json['uid']),
      cfgs: serializer.fromJson<String>(json['cfgs']),
      tag: serializer.fromJson<String>(json['tag']),
      tagName: serializer.fromJson<String>(json['tagName']),
      type: serializer.fromJson<int>(json['type']),
      status: serializer.fromJson<String>(json['status']),
    );
  }
  @override
  Map<String, dynamic> toJson({ValueSerializer? serializer}) {
    serializer ??= driftRuntimeOptions.defaultSerializer;
    return <String, dynamic>{
      'uid': serializer.toJson<String>(uid),
      'cfgs': serializer.toJson<String>(cfgs),
      'tag': serializer.toJson<String>(tag),
      'tagName': serializer.toJson<String>(tagName),
      'type': serializer.toJson<int>(type),
      'status': serializer.toJson<String>(status),
    };
  }

  FlutterJusRelationData copyWith(
          {String? uid,
          String? cfgs,
          String? tag,
          String? tagName,
          int? type,
          String? status}) =>
      FlutterJusRelationData(
        uid: uid ?? this.uid,
        cfgs: cfgs ?? this.cfgs,
        tag: tag ?? this.tag,
        tagName: tagName ?? this.tagName,
        type: type ?? this.type,
        status: status ?? this.status,
      );
  FlutterJusRelationData copyWithCompanion(FlutterJusRelationCompanion data) {
    return FlutterJusRelationData(
      uid: data.uid.present ? data.uid.value : this.uid,
      cfgs: data.cfgs.present ? data.cfgs.value : this.cfgs,
      tag: data.tag.present ? data.tag.value : this.tag,
      tagName: data.tagName.present ? data.tagName.value : this.tagName,
      type: data.type.present ? data.type.value : this.type,
      status: data.status.present ? data.status.value : this.status,
    );
  }

  @override
  String toString() {
    return (StringBuffer('FlutterJusRelationData(')
          ..write('uid: $uid, ')
          ..write('cfgs: $cfgs, ')
          ..write('tag: $tag, ')
          ..write('tagName: $tagName, ')
          ..write('type: $type, ')
          ..write('status: $status')
          ..write(')'))
        .toString();
  }

  @override
  int get hashCode => Object.hash(uid, cfgs, tag, tagName, type, status);
  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      (other is FlutterJusRelationData &&
          other.uid == this.uid &&
          other.cfgs == this.cfgs &&
          other.tag == this.tag &&
          other.tagName == this.tagName &&
          other.type == this.type &&
          other.status == this.status);
}

class FlutterJusRelationCompanion
    extends UpdateCompanion<FlutterJusRelationData> {
  final Value<String> uid;
  final Value<String> cfgs;
  final Value<String> tag;
  final Value<String> tagName;
  final Value<int> type;
  final Value<String> status;
  final Value<int> rowid;
  const FlutterJusRelationCompanion({
    this.uid = const Value.absent(),
    this.cfgs = const Value.absent(),
    this.tag = const Value.absent(),
    this.tagName = const Value.absent(),
    this.type = const Value.absent(),
    this.status = const Value.absent(),
    this.rowid = const Value.absent(),
  });
  FlutterJusRelationCompanion.insert({
    required String uid,
    required String cfgs,
    required String tag,
    required String tagName,
    required int type,
    required String status,
    this.rowid = const Value.absent(),
  })  : uid = Value(uid),
        cfgs = Value(cfgs),
        tag = Value(tag),
        tagName = Value(tagName),
        type = Value(type),
        status = Value(status);
  static Insertable<FlutterJusRelationData> custom({
    Expression<String>? uid,
    Expression<String>? cfgs,
    Expression<String>? tag,
    Expression<String>? tagName,
    Expression<int>? type,
    Expression<String>? status,
    Expression<int>? rowid,
  }) {
    return RawValuesInsertable({
      if (uid != null) 'uid': uid,
      if (cfgs != null) 'cfgs': cfgs,
      if (tag != null) 'tag': tag,
      if (tagName != null) 'tag_name': tagName,
      if (type != null) 'type': type,
      if (status != null) 'status': status,
      if (rowid != null) 'rowid': rowid,
    });
  }

  FlutterJusRelationCompanion copyWith(
      {Value<String>? uid,
      Value<String>? cfgs,
      Value<String>? tag,
      Value<String>? tagName,
      Value<int>? type,
      Value<String>? status,
      Value<int>? rowid}) {
    return FlutterJusRelationCompanion(
      uid: uid ?? this.uid,
      cfgs: cfgs ?? this.cfgs,
      tag: tag ?? this.tag,
      tagName: tagName ?? this.tagName,
      type: type ?? this.type,
      status: status ?? this.status,
      rowid: rowid ?? this.rowid,
    );
  }

  @override
  Map<String, Expression> toColumns(bool nullToAbsent) {
    final map = <String, Expression>{};
    if (uid.present) {
      map['uid'] = Variable<String>(uid.value);
    }
    if (cfgs.present) {
      map['cfgs'] = Variable<String>(cfgs.value);
    }
    if (tag.present) {
      map['tag'] = Variable<String>(tag.value);
    }
    if (tagName.present) {
      map['tag_name'] = Variable<String>(tagName.value);
    }
    if (type.present) {
      map['type'] = Variable<int>(type.value);
    }
    if (status.present) {
      map['status'] = Variable<String>(status.value);
    }
    if (rowid.present) {
      map['rowid'] = Variable<int>(rowid.value);
    }
    return map;
  }

  @override
  String toString() {
    return (StringBuffer('FlutterJusRelationCompanion(')
          ..write('uid: $uid, ')
          ..write('cfgs: $cfgs, ')
          ..write('tag: $tag, ')
          ..write('tagName: $tagName, ')
          ..write('type: $type, ')
          ..write('status: $status, ')
          ..write('rowid: $rowid')
          ..write(')'))
        .toString();
  }
}

abstract class _$FlutterJusAppDatabase extends GeneratedDatabase {
  _$FlutterJusAppDatabase(QueryExecutor e) : super(e);
  $FlutterJusAppDatabaseManager get managers =>
      $FlutterJusAppDatabaseManager(this);
  late final $FlutterJusRelationTable flutterJusRelation =
      $FlutterJusRelationTable(this);
  @override
  Iterable<TableInfo<Table, Object?>> get allTables =>
      allSchemaEntities.whereType<TableInfo<Table, Object?>>();
  @override
  List<DatabaseSchemaEntity> get allSchemaEntities => [flutterJusRelation];
}

typedef $$FlutterJusRelationTableCreateCompanionBuilder
    = FlutterJusRelationCompanion Function({
  required String uid,
  required String cfgs,
  required String tag,
  required String tagName,
  required int type,
  required String status,
  Value<int> rowid,
});
typedef $$FlutterJusRelationTableUpdateCompanionBuilder
    = FlutterJusRelationCompanion Function({
  Value<String> uid,
  Value<String> cfgs,
  Value<String> tag,
  Value<String> tagName,
  Value<int> type,
  Value<String> status,
  Value<int> rowid,
});

class $$FlutterJusRelationTableFilterComposer
    extends FilterComposer<_$FlutterJusAppDatabase, $FlutterJusRelationTable> {
  $$FlutterJusRelationTableFilterComposer(super.$state);
  ColumnFilters<String> get uid => $state.composableBuilder(
      column: $state.table.uid,
      builder: (column, joinBuilders) =>
          ColumnFilters(column, joinBuilders: joinBuilders));

  ColumnFilters<String> get cfgs => $state.composableBuilder(
      column: $state.table.cfgs,
      builder: (column, joinBuilders) =>
          ColumnFilters(column, joinBuilders: joinBuilders));

  ColumnFilters<String> get tag => $state.composableBuilder(
      column: $state.table.tag,
      builder: (column, joinBuilders) =>
          ColumnFilters(column, joinBuilders: joinBuilders));

  ColumnFilters<String> get tagName => $state.composableBuilder(
      column: $state.table.tagName,
      builder: (column, joinBuilders) =>
          ColumnFilters(column, joinBuilders: joinBuilders));

  ColumnFilters<int> get type => $state.composableBuilder(
      column: $state.table.type,
      builder: (column, joinBuilders) =>
          ColumnFilters(column, joinBuilders: joinBuilders));

  ColumnFilters<String> get status => $state.composableBuilder(
      column: $state.table.status,
      builder: (column, joinBuilders) =>
          ColumnFilters(column, joinBuilders: joinBuilders));
}

class $$FlutterJusRelationTableOrderingComposer extends OrderingComposer<
    _$FlutterJusAppDatabase, $FlutterJusRelationTable> {
  $$FlutterJusRelationTableOrderingComposer(super.$state);
  ColumnOrderings<String> get uid => $state.composableBuilder(
      column: $state.table.uid,
      builder: (column, joinBuilders) =>
          ColumnOrderings(column, joinBuilders: joinBuilders));

  ColumnOrderings<String> get cfgs => $state.composableBuilder(
      column: $state.table.cfgs,
      builder: (column, joinBuilders) =>
          ColumnOrderings(column, joinBuilders: joinBuilders));

  ColumnOrderings<String> get tag => $state.composableBuilder(
      column: $state.table.tag,
      builder: (column, joinBuilders) =>
          ColumnOrderings(column, joinBuilders: joinBuilders));

  ColumnOrderings<String> get tagName => $state.composableBuilder(
      column: $state.table.tagName,
      builder: (column, joinBuilders) =>
          ColumnOrderings(column, joinBuilders: joinBuilders));

  ColumnOrderings<int> get type => $state.composableBuilder(
      column: $state.table.type,
      builder: (column, joinBuilders) =>
          ColumnOrderings(column, joinBuilders: joinBuilders));

  ColumnOrderings<String> get status => $state.composableBuilder(
      column: $state.table.status,
      builder: (column, joinBuilders) =>
          ColumnOrderings(column, joinBuilders: joinBuilders));
}

class $$FlutterJusRelationTableTableManager extends RootTableManager<
    _$FlutterJusAppDatabase,
    $FlutterJusRelationTable,
    FlutterJusRelationData,
    $$FlutterJusRelationTableFilterComposer,
    $$FlutterJusRelationTableOrderingComposer,
    $$FlutterJusRelationTableCreateCompanionBuilder,
    $$FlutterJusRelationTableUpdateCompanionBuilder,
    (
      FlutterJusRelationData,
      BaseReferences<_$FlutterJusAppDatabase, $FlutterJusRelationTable,
          FlutterJusRelationData>
    ),
    FlutterJusRelationData,
    PrefetchHooks Function()> {
  $$FlutterJusRelationTableTableManager(
      _$FlutterJusAppDatabase db, $FlutterJusRelationTable table)
      : super(TableManagerState(
          db: db,
          table: table,
          filteringComposer:
              $$FlutterJusRelationTableFilterComposer(ComposerState(db, table)),
          orderingComposer: $$FlutterJusRelationTableOrderingComposer(
              ComposerState(db, table)),
          updateCompanionCallback: ({
            Value<String> uid = const Value.absent(),
            Value<String> cfgs = const Value.absent(),
            Value<String> tag = const Value.absent(),
            Value<String> tagName = const Value.absent(),
            Value<int> type = const Value.absent(),
            Value<String> status = const Value.absent(),
            Value<int> rowid = const Value.absent(),
          }) =>
              FlutterJusRelationCompanion(
            uid: uid,
            cfgs: cfgs,
            tag: tag,
            tagName: tagName,
            type: type,
            status: status,
            rowid: rowid,
          ),
          createCompanionCallback: ({
            required String uid,
            required String cfgs,
            required String tag,
            required String tagName,
            required int type,
            required String status,
            Value<int> rowid = const Value.absent(),
          }) =>
              FlutterJusRelationCompanion.insert(
            uid: uid,
            cfgs: cfgs,
            tag: tag,
            tagName: tagName,
            type: type,
            status: status,
            rowid: rowid,
          ),
          withReferenceMapper: (p0) => p0
              .map((e) => (e.readTable(table), BaseReferences(db, table, e)))
              .toList(),
          prefetchHooksCallback: null,
        ));
}

typedef $$FlutterJusRelationTableProcessedTableManager = ProcessedTableManager<
    _$FlutterJusAppDatabase,
    $FlutterJusRelationTable,
    FlutterJusRelationData,
    $$FlutterJusRelationTableFilterComposer,
    $$FlutterJusRelationTableOrderingComposer,
    $$FlutterJusRelationTableCreateCompanionBuilder,
    $$FlutterJusRelationTableUpdateCompanionBuilder,
    (
      FlutterJusRelationData,
      BaseReferences<_$FlutterJusAppDatabase, $FlutterJusRelationTable,
          FlutterJusRelationData>
    ),
    FlutterJusRelationData,
    PrefetchHooks Function()>;

class $FlutterJusAppDatabaseManager {
  final _$FlutterJusAppDatabase _db;
  $FlutterJusAppDatabaseManager(this._db);
  $$FlutterJusRelationTableTableManager get flutterJusRelation =>
      $$FlutterJusRelationTableTableManager(_db, _db.flutterJusRelation);
}
