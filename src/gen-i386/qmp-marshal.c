/* AUTOMATICALLY GENERATED, DO NOT MODIFY */

/*
 * schema-defined QMP->QAPI command dispatch
 *
 * Copyright IBM, Corp. 2011
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "qemu/module.h"
#include "qapi/qmp/types.h"
#include "qapi/qmp/dispatch.h"
#include "qapi/visitor.h"
#include "qapi/qmp-output-visitor.h"
#include "qapi/qmp-input-visitor.h"
#include "qapi/dealloc-visitor.h"
#include "qapi-types.h"
#include "qapi-visit.h"
#include "qmp-commands.h"


static void qmp_marshal_output_AddfdInfo(AddfdInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_AddfdInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_AddfdInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_add_fd(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    AddfdInfo *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_add_fd_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_add_fd_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_add_fd(arg.has_fdset_id, arg.fdset_id, arg.has_opaque, arg.opaque, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_AddfdInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_add_fd_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_add_client(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_add_client_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_add_client_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_add_client(arg.protocol, arg.fdname, arg.has_skipauth, arg.skipauth, arg.has_tls, arg.tls, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_add_client_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_balloon(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_balloon_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_balloon_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_balloon(arg.value, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_balloon_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_commit(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_commit_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_commit_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_commit(arg.device, arg.has_base, arg.base, arg.has_top, arg.top, arg.has_backing_file, arg.backing_file, arg.has_speed, arg.speed, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_commit_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_dirty_bitmap_add(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockDirtyBitmapAdd arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockDirtyBitmapAdd_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_dirty_bitmap_add(arg.node, arg.name, arg.has_granularity, arg.granularity, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockDirtyBitmapAdd_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_dirty_bitmap_clear(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockDirtyBitmap arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockDirtyBitmap_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_dirty_bitmap_clear(arg.node, arg.name, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockDirtyBitmap_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_dirty_bitmap_remove(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockDirtyBitmap arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockDirtyBitmap_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_dirty_bitmap_remove(arg.node, arg.name, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockDirtyBitmap_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_job_cancel(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_job_cancel_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_job_cancel_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_job_cancel(arg.device, arg.has_force, arg.force, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_job_cancel_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_job_complete(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_job_complete_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_job_complete_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_job_complete(arg.device, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_job_complete_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_job_pause(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_job_pause_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_job_pause_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_job_pause(arg.device, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_job_pause_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_job_resume(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_job_resume_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_job_resume_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_job_resume(arg.device, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_job_resume_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_job_set_speed(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_job_set_speed_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_job_set_speed_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_job_set_speed(arg.device, arg.speed, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_job_set_speed_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_set_write_threshold(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_set_write_threshold_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_set_write_threshold_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_set_write_threshold(arg.node_name, arg.write_threshold, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_set_write_threshold_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_stream(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_stream_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_stream_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_stream(arg.device, arg.has_base, arg.base, arg.has_backing_file, arg.backing_file, arg.has_speed, arg.speed, arg.has_on_error, arg.on_error, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_stream_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_passwd(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_passwd_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_passwd_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_passwd(arg.has_device, arg.device, arg.has_node_name, arg.node_name, arg.password, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_passwd_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_resize(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_resize_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_resize_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_resize(arg.has_device, arg.device, arg.has_node_name, arg.node_name, arg.size, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_resize_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_block_set_io_throttle(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_block_set_io_throttle_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_block_set_io_throttle_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_block_set_io_throttle(arg.device, arg.bps, arg.bps_rd, arg.bps_wr, arg.iops, arg.iops_rd, arg.iops_wr, arg.has_bps_max, arg.bps_max, arg.has_bps_rd_max, arg.bps_rd_max, arg.has_bps_wr_max, arg.bps_wr_max, arg.has_iops_max, arg.iops_max, arg.has_iops_rd_max, arg.iops_rd_max, arg.has_iops_wr_max, arg.iops_wr_max, arg.has_bps_max_length, arg.bps_max_length, arg.has_bps_rd_max_length, arg.bps_rd_max_length, arg.has_bps_wr_max_length, arg.bps_wr_max_length, arg.has_iops_max_length, arg.iops_max_length, arg.has_iops_rd_max_length, arg.iops_rd_max_length, arg.has_iops_wr_max_length, arg.iops_wr_max_length, arg.has_iops_size, arg.iops_size, arg.has_group, arg.group, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_block_set_io_throttle_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_add(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_blockdev_add_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_blockdev_add_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_add(arg.options, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_blockdev_add_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_backup(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockdevBackup arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockdevBackup_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_backup(arg.device, arg.target, arg.sync, arg.has_speed, arg.speed, arg.has_on_source_error, arg.on_source_error, arg.has_on_target_error, arg.on_target_error, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockdevBackup_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_change_medium(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_blockdev_change_medium_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_blockdev_change_medium_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_change_medium(arg.device, arg.filename, arg.has_format, arg.format, arg.has_read_only_mode, arg.read_only_mode, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_blockdev_change_medium_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_close_tray(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_blockdev_close_tray_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_blockdev_close_tray_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_close_tray(arg.device, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_blockdev_close_tray_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_mirror(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_blockdev_mirror_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_blockdev_mirror_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_mirror(arg.device, arg.target, arg.has_replaces, arg.replaces, arg.sync, arg.has_speed, arg.speed, arg.has_granularity, arg.granularity, arg.has_buf_size, arg.buf_size, arg.has_on_source_error, arg.on_source_error, arg.has_on_target_error, arg.on_target_error, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_blockdev_mirror_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_open_tray(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_blockdev_open_tray_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_blockdev_open_tray_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_open_tray(arg.device, arg.has_force, arg.force, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_blockdev_open_tray_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_snapshot(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockdevSnapshot arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockdevSnapshot_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_snapshot(arg.node, arg.overlay, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockdevSnapshot_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_SnapshotInfo(SnapshotInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_SnapshotInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_SnapshotInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_snapshot_delete_internal_sync(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    SnapshotInfo *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_blockdev_snapshot_delete_internal_sync_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_blockdev_snapshot_delete_internal_sync_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_blockdev_snapshot_delete_internal_sync(arg.device, arg.has_id, arg.id, arg.has_name, arg.name, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_SnapshotInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_blockdev_snapshot_delete_internal_sync_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_snapshot_internal_sync(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockdevSnapshotInternal arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockdevSnapshotInternal_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_snapshot_internal_sync(arg.device, arg.name, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockdevSnapshotInternal_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_blockdev_snapshot_sync(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    BlockdevSnapshotSync arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_BlockdevSnapshotSync_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_blockdev_snapshot_sync(arg.has_device, arg.device, arg.has_node_name, arg.node_name, arg.snapshot_file, arg.has_snapshot_node_name, arg.snapshot_node_name, arg.has_format, arg.format, arg.has_mode, arg.mode, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockdevSnapshotSync_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_change(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_change_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_change_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_change(arg.device, arg.target, arg.has_arg, arg.arg, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_change_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_change_backing_file(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_change_backing_file_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_change_backing_file_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_change_backing_file(arg.device, arg.image_node_name, arg.backing_file, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_change_backing_file_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_change_vnc_password(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_change_vnc_password_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_change_vnc_password_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_change_vnc_password(arg.password, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_change_vnc_password_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_ChardevReturn(ChardevReturn *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_ChardevReturn(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_ChardevReturn(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_chardev_add(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    ChardevReturn *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_chardev_add_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_chardev_add_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_chardev_add(arg.id, arg.backend, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_ChardevReturn(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_chardev_add_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_chardev_remove(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_chardev_remove_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_chardev_remove_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_chardev_remove(arg.id, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_chardev_remove_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_client_migrate_info(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_client_migrate_info_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_client_migrate_info_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_client_migrate_info(arg.protocol, arg.hostname, arg.has_port, arg.port, arg.has_tls_port, arg.tls_port, arg.has_cert_subject, arg.cert_subject, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_client_migrate_info_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_closefd(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_closefd_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_closefd_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_closefd(arg.fdname, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_closefd_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_cont(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_cont(&err);
    error_propagate(errp, err);
}

void qmp_marshal_cpu(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_cpu_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_cpu_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_cpu(arg.index, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_cpu_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_cpu_add(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_cpu_add_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_cpu_add_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_cpu_add(arg.id, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_cpu_add_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_DevicePropertyInfoList(DevicePropertyInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_DevicePropertyInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_DevicePropertyInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_device_list_properties(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    DevicePropertyInfoList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_device_list_properties_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_device_list_properties_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_device_list_properties(arg.q_typename, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_DevicePropertyInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_device_list_properties_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_device_del(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_device_del_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_device_del_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_device_del(arg.id, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_device_del_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_drive_backup(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    DriveBackup arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_DriveBackup_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_drive_backup(arg.device, arg.target, arg.has_format, arg.format, arg.sync, arg.has_mode, arg.mode, arg.has_speed, arg.speed, arg.has_bitmap, arg.bitmap, arg.has_on_source_error, arg.on_source_error, arg.has_on_target_error, arg.on_target_error, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_DriveBackup_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_drive_mirror(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_drive_mirror_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_drive_mirror_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_drive_mirror(arg.device, arg.target, arg.has_format, arg.format, arg.has_node_name, arg.node_name, arg.has_replaces, arg.replaces, arg.sync, arg.has_mode, arg.mode, arg.has_speed, arg.speed, arg.has_granularity, arg.granularity, arg.has_buf_size, arg.buf_size, arg.has_on_source_error, arg.on_source_error, arg.has_on_target_error, arg.on_target_error, arg.has_unmap, arg.unmap, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_drive_mirror_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_dump_guest_memory(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_dump_guest_memory_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_dump_guest_memory_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_dump_guest_memory(arg.paging, arg.protocol, arg.has_detach, arg.detach, arg.has_begin, arg.begin, arg.has_length, arg.length, arg.has_format, arg.format, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_dump_guest_memory_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_dump_skeys(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_dump_skeys_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_dump_skeys_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_dump_skeys(arg.filename, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_dump_skeys_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_eject(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_eject_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_eject_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_eject(arg.device, arg.has_force, arg.force, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_eject_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_expire_password(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_expire_password_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_expire_password_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_expire_password(arg.protocol, arg.time, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_expire_password_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_getfd(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_getfd_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_getfd_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_getfd(arg.fdname, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_getfd_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_str(char *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_str(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_str(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_human_monitor_command(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    char *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_human_monitor_command_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_human_monitor_command_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_human_monitor_command(arg.command_line, arg.has_cpu_index, arg.cpu_index, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_str(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_human_monitor_command_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_inject_nmi(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_inject_nmi(&err);
    error_propagate(errp, err);
}

void qmp_marshal_input_send_event(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_input_send_event_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_input_send_event_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_input_send_event(arg.has_device, arg.device, arg.has_head, arg.head, arg.events, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_input_send_event_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_memsave(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_memsave_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_memsave_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_memsave(arg.val, arg.size, arg.filename, arg.has_cpu_index, arg.cpu_index, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_memsave_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate(arg.uri, arg.has_blk, arg.blk, arg.has_inc, arg.inc, arg.has_detach, arg.detach, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate_incoming(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_incoming_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_incoming_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate_incoming(arg.uri, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_incoming_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate_set_cache_size(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_set_cache_size_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_set_cache_size_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate_set_cache_size(arg.value, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_set_cache_size_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate_set_capabilities(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_set_capabilities_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_set_capabilities_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate_set_capabilities(arg.capabilities, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_set_capabilities_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate_set_parameters(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_set_parameters_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_set_parameters_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate_set_parameters(arg.has_compress_level, arg.compress_level, arg.has_compress_threads, arg.compress_threads, arg.has_decompress_threads, arg.decompress_threads, arg.has_x_cpu_throttle_initial, arg.x_cpu_throttle_initial, arg.has_x_cpu_throttle_increment, arg.x_cpu_throttle_increment, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_set_parameters_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate_start_postcopy(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_migrate_start_postcopy(&err);
    error_propagate(errp, err);
}

void qmp_marshal_migrate_cancel(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_migrate_cancel(&err);
    error_propagate(errp, err);
}

void qmp_marshal_migrate_set_downtime(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_set_downtime_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_set_downtime_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate_set_downtime(arg.value, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_set_downtime_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_migrate_set_speed(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_migrate_set_speed_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_migrate_set_speed_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_migrate_set_speed(arg.value, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_migrate_set_speed_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_nbd_server_add(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_nbd_server_add_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_nbd_server_add_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_nbd_server_add(arg.device, arg.has_writable, arg.writable, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_nbd_server_add_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_nbd_server_start(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_nbd_server_start_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_nbd_server_start_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_nbd_server_start(arg.addr, arg.has_tls_creds, arg.tls_creds, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_nbd_server_start_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_nbd_server_stop(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_nbd_server_stop(&err);
    error_propagate(errp, err);
}

void qmp_marshal_netdev_del(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_netdev_del_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_netdev_del_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_netdev_del(arg.id, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_netdev_del_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_object_add(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_object_add_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_object_add_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_object_add(arg.qom_type, arg.id, arg.has_props, arg.props, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_object_add_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_object_del(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_object_del_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_object_del_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_object_del(arg.id, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_object_del_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_pmemsave(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_pmemsave_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_pmemsave_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_pmemsave(arg.val, arg.size, arg.filename, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_pmemsave_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_any(QObject *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_any(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_any(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_qom_get(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QObject *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_qom_get_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_qom_get_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_qom_get(arg.path, arg.property, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_any(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_qom_get_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_ObjectPropertyInfoList(ObjectPropertyInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_ObjectPropertyInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_ObjectPropertyInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_qom_list(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    ObjectPropertyInfoList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_qom_list_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_qom_list_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_qom_list(arg.path, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_ObjectPropertyInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_qom_list_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_ObjectTypeInfoList(ObjectTypeInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_ObjectTypeInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_ObjectTypeInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_qom_list_types(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    ObjectTypeInfoList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_qom_list_types_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_qom_list_types_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_qom_list_types(arg.has_implements, arg.implements, arg.has_abstract, arg.abstract, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_ObjectTypeInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_qom_list_types_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_qom_set(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_qom_set_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_qom_set_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_qom_set(arg.path, arg.property, arg.value, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_qom_set_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_ACPIOSTInfoList(ACPIOSTInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_ACPIOSTInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_ACPIOSTInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_acpi_ospm_status(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    ACPIOSTInfoList *retval;

    (void)args;

    retval = qmp_query_acpi_ospm_status(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_ACPIOSTInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_BalloonInfo(BalloonInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_BalloonInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BalloonInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_balloon(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    BalloonInfo *retval;

    (void)args;

    retval = qmp_query_balloon(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_BalloonInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_BlockInfoList(BlockInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_BlockInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_block(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    BlockInfoList *retval;

    (void)args;

    retval = qmp_query_block(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_BlockInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_BlockJobInfoList(BlockJobInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_BlockJobInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockJobInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_block_jobs(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    BlockJobInfoList *retval;

    (void)args;

    retval = qmp_query_block_jobs(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_BlockJobInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_BlockStatsList(BlockStatsList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_BlockStatsList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockStatsList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_blockstats(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    BlockStatsList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_blockstats_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_blockstats_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_blockstats(arg.has_query_nodes, arg.query_nodes, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_BlockStatsList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_blockstats_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_ChardevInfoList(ChardevInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_ChardevInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_ChardevInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_chardev(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    ChardevInfoList *retval;

    (void)args;

    retval = qmp_query_chardev(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_ChardevInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_ChardevBackendInfoList(ChardevBackendInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_ChardevBackendInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_ChardevBackendInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_chardev_backends(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    ChardevBackendInfoList *retval;

    (void)args;

    retval = qmp_query_chardev_backends(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_ChardevBackendInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_CommandLineOptionInfoList(CommandLineOptionInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_CommandLineOptionInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_CommandLineOptionInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_command_line_options(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    CommandLineOptionInfoList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_command_line_options_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_command_line_options_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_command_line_options(arg.has_option, arg.option, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_CommandLineOptionInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_command_line_options_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_CommandInfoList(CommandInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_CommandInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_CommandInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_commands(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    CommandInfoList *retval;

    (void)args;

    retval = qmp_query_commands(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_CommandInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_CpuDefinitionInfoList(CpuDefinitionInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_CpuDefinitionInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_CpuDefinitionInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_cpu_definitions(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    CpuDefinitionInfoList *retval;

    (void)args;

    retval = qmp_query_cpu_definitions(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_CpuDefinitionInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_CpuInfoList(CpuInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_CpuInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_CpuInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_cpus(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    CpuInfoList *retval;

    (void)args;

    retval = qmp_query_cpus(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_CpuInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_DumpQueryResult(DumpQueryResult *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_DumpQueryResult(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_DumpQueryResult(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_dump(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    DumpQueryResult *retval;

    (void)args;

    retval = qmp_query_dump(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_DumpQueryResult(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_DumpGuestMemoryCapability(DumpGuestMemoryCapability *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_DumpGuestMemoryCapability(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_DumpGuestMemoryCapability(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_dump_guest_memory_capability(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    DumpGuestMemoryCapability *retval;

    (void)args;

    retval = qmp_query_dump_guest_memory_capability(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_DumpGuestMemoryCapability(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_EventInfoList(EventInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_EventInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_EventInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_events(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    EventInfoList *retval;

    (void)args;

    retval = qmp_query_events(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_EventInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_FdsetInfoList(FdsetInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_FdsetInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_FdsetInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_fdsets(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    FdsetInfoList *retval;

    (void)args;

    retval = qmp_query_fdsets(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_FdsetInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_GICCapabilityList(GICCapabilityList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_GICCapabilityList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_GICCapabilityList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_gic_capabilities(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    GICCapabilityList *retval;

    (void)args;

    retval = qmp_query_gic_capabilities(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_GICCapabilityList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_IOThreadInfoList(IOThreadInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_IOThreadInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_IOThreadInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_iothreads(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    IOThreadInfoList *retval;

    (void)args;

    retval = qmp_query_iothreads(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_IOThreadInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_KvmInfo(KvmInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_KvmInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_KvmInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_kvm(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    KvmInfo *retval;

    (void)args;

    retval = qmp_query_kvm(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_KvmInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MachineInfoList(MachineInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MachineInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MachineInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_machines(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MachineInfoList *retval;

    (void)args;

    retval = qmp_query_machines(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MachineInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MemdevList(MemdevList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MemdevList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MemdevList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_memdev(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MemdevList *retval;

    (void)args;

    retval = qmp_query_memdev(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MemdevList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MemoryDeviceInfoList(MemoryDeviceInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MemoryDeviceInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MemoryDeviceInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_memory_devices(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MemoryDeviceInfoList *retval;

    (void)args;

    retval = qmp_query_memory_devices(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MemoryDeviceInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MouseInfoList(MouseInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MouseInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MouseInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_mice(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MouseInfoList *retval;

    (void)args;

    retval = qmp_query_mice(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MouseInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MigrationInfo(MigrationInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MigrationInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MigrationInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_migrate(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MigrationInfo *retval;

    (void)args;

    retval = qmp_query_migrate(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MigrationInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_int(int64_t ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_int(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_int(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_migrate_cache_size(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    int64_t retval;

    (void)args;

    retval = qmp_query_migrate_cache_size(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_int(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MigrationCapabilityStatusList(MigrationCapabilityStatusList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MigrationCapabilityStatusList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MigrationCapabilityStatusList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_migrate_capabilities(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MigrationCapabilityStatusList *retval;

    (void)args;

    retval = qmp_query_migrate_capabilities(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MigrationCapabilityStatusList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_MigrationParameters(MigrationParameters *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_MigrationParameters(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_MigrationParameters(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_migrate_parameters(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    MigrationParameters *retval;

    (void)args;

    retval = qmp_query_migrate_parameters(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_MigrationParameters(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_NameInfo(NameInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_NameInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_NameInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_name(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    NameInfo *retval;

    (void)args;

    retval = qmp_query_name(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_NameInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_BlockDeviceInfoList(BlockDeviceInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_BlockDeviceInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_BlockDeviceInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_named_block_nodes(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    BlockDeviceInfoList *retval;

    (void)args;

    retval = qmp_query_named_block_nodes(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_BlockDeviceInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_PciInfoList(PciInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_PciInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_PciInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_pci(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    PciInfoList *retval;

    (void)args;

    retval = qmp_query_pci(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_PciInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_RockerSwitch(RockerSwitch *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_RockerSwitch(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_RockerSwitch(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_rocker(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    RockerSwitch *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_rocker_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_rocker_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_rocker(arg.name, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_RockerSwitch(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_rocker_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_RockerOfDpaFlowList(RockerOfDpaFlowList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_RockerOfDpaFlowList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_RockerOfDpaFlowList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_rocker_of_dpa_flows(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    RockerOfDpaFlowList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_rocker_of_dpa_flows_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_rocker_of_dpa_flows_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_rocker_of_dpa_flows(arg.name, arg.has_tbl_id, arg.tbl_id, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_RockerOfDpaFlowList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_rocker_of_dpa_flows_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_RockerOfDpaGroupList(RockerOfDpaGroupList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_RockerOfDpaGroupList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_RockerOfDpaGroupList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_rocker_of_dpa_groups(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    RockerOfDpaGroupList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_rocker_of_dpa_groups_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_rocker_of_dpa_groups_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_rocker_of_dpa_groups(arg.name, arg.has_type, arg.type, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_RockerOfDpaGroupList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_rocker_of_dpa_groups_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_RockerPortList(RockerPortList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_RockerPortList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_RockerPortList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_rocker_ports(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    RockerPortList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_rocker_ports_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_rocker_ports_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_rocker_ports(arg.name, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_RockerPortList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_rocker_ports_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_RxFilterInfoList(RxFilterInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_RxFilterInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_RxFilterInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_rx_filter(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    RxFilterInfoList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_query_rx_filter_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_query_rx_filter_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_query_rx_filter(arg.has_name, arg.name, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_RxFilterInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_query_rx_filter_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

static void qmp_marshal_output_SpiceInfo(SpiceInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_SpiceInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_SpiceInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_spice(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    SpiceInfo *retval;

    (void)args;

    retval = qmp_query_spice(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_SpiceInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_StatusInfo(StatusInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_StatusInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_StatusInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_status(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    StatusInfo *retval;

    (void)args;

    retval = qmp_query_status(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_StatusInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_TargetInfo(TargetInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_TargetInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_TargetInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_target(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    TargetInfo *retval;

    (void)args;

    retval = qmp_query_target(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_TargetInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_TPMInfoList(TPMInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_TPMInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_TPMInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_tpm(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    TPMInfoList *retval;

    (void)args;

    retval = qmp_query_tpm(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_TPMInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_TpmModelList(TpmModelList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_TpmModelList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_TpmModelList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_tpm_models(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    TpmModelList *retval;

    (void)args;

    retval = qmp_query_tpm_models(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_TpmModelList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_TpmTypeList(TpmTypeList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_TpmTypeList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_TpmTypeList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_tpm_types(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    TpmTypeList *retval;

    (void)args;

    retval = qmp_query_tpm_types(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_TpmTypeList(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_UuidInfo(UuidInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_UuidInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_UuidInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_uuid(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    UuidInfo *retval;

    (void)args;

    retval = qmp_query_uuid(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_UuidInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_VersionInfo(VersionInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_VersionInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_VersionInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_version(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    VersionInfo *retval;

    (void)args;

    retval = qmp_query_version(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_VersionInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_VncInfo(VncInfo *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_VncInfo(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_VncInfo(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_vnc(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    VncInfo *retval;

    (void)args;

    retval = qmp_query_vnc(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_VncInfo(retval, ret, &err);

out:
    error_propagate(errp, err);
}

static void qmp_marshal_output_VncInfo2List(VncInfo2List *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_VncInfo2List(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_VncInfo2List(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_query_vnc_servers(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    VncInfo2List *retval;

    (void)args;

    retval = qmp_query_vnc_servers(&err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_VncInfo2List(retval, ret, &err);

out:
    error_propagate(errp, err);
}

void qmp_marshal_quit(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_quit(&err);
    error_propagate(errp, err);
}

void qmp_marshal_remove_fd(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_remove_fd_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_remove_fd_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_remove_fd(arg.fdset_id, arg.has_fd, arg.fd, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_remove_fd_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_ringbuf_read(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    char *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_ringbuf_read_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_ringbuf_read_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_ringbuf_read(arg.device, arg.size, arg.has_format, arg.format, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_str(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_ringbuf_read_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_ringbuf_write(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_ringbuf_write_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_ringbuf_write_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_ringbuf_write(arg.device, arg.data, arg.has_format, arg.format, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_ringbuf_write_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_rtc_reset_reinjection(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_rtc_reset_reinjection(&err);
    error_propagate(errp, err);
}

void qmp_marshal_screendump(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_screendump_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_screendump_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_screendump(arg.filename, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_screendump_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_send_key(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_send_key_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_send_key_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_send_key(arg.keys, arg.has_hold_time, arg.hold_time, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_send_key_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_set_link(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_set_link_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_set_link_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_set_link(arg.name, arg.up, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_set_link_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_set_password(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_set_password_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_set_password_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_set_password(arg.protocol, arg.password, arg.has_connected, arg.connected, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_set_password_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_stop(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_stop(&err);
    error_propagate(errp, err);
}

void qmp_marshal_system_powerdown(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_system_powerdown(&err);
    error_propagate(errp, err);
}

void qmp_marshal_system_reset(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_system_reset(&err);
    error_propagate(errp, err);
}

void qmp_marshal_system_wakeup(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;

    (void)args;

    qmp_system_wakeup(&err);
    error_propagate(errp, err);
}

static void qmp_marshal_output_TraceEventInfoList(TraceEventInfoList *ret_in, QObject **ret_out, Error **errp)
{
    Error *err = NULL;
    QmpOutputVisitor *qov = qmp_output_visitor_new();
    QapiDeallocVisitor *qdv;
    Visitor *v;

    v = qmp_output_get_visitor(qov);
    visit_type_TraceEventInfoList(v, "unused", &ret_in, &err);
    if (err) {
        goto out;
    }
    *ret_out = qmp_output_get_qobject(qov);

out:
    error_propagate(errp, err);
    qmp_output_visitor_cleanup(qov);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_TraceEventInfoList(v, "unused", &ret_in, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_trace_event_get_state(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    TraceEventInfoList *retval;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_trace_event_get_state_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_trace_event_get_state_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    retval = qmp_trace_event_get_state(arg.name, &err);
    if (err) {
        goto out;
    }

    qmp_marshal_output_TraceEventInfoList(retval, ret, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_trace_event_get_state_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_trace_event_set_state(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_trace_event_set_state_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_trace_event_set_state_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_trace_event_set_state(arg.name, arg.enable, arg.has_ignore_unavailable, arg.ignore_unavailable, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_trace_event_set_state_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_transaction(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_transaction_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_transaction_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_transaction(arg.actions, arg.has_properties, arg.properties, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_transaction_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_x_blockdev_del(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_x_blockdev_del_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_x_blockdev_del_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_x_blockdev_del(arg.has_id, arg.id, arg.has_node_name, arg.node_name, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_x_blockdev_del_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_x_blockdev_insert_medium(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_x_blockdev_insert_medium_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_x_blockdev_insert_medium_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_x_blockdev_insert_medium(arg.device, arg.node_name, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_x_blockdev_insert_medium_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_x_blockdev_remove_medium(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_x_blockdev_remove_medium_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_x_blockdev_remove_medium_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_x_blockdev_remove_medium(arg.device, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_x_blockdev_remove_medium_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_xen_save_devices_state(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_xen_save_devices_state_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_xen_save_devices_state_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_xen_save_devices_state(arg.filename, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_xen_save_devices_state_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}

void qmp_marshal_xen_set_global_dirty_log(QDict *args, QObject **ret, Error **errp)
{
    Error *err = NULL;
    QmpInputVisitor *qiv = qmp_input_visitor_new_strict(QOBJECT(args));
    QapiDeallocVisitor *qdv;
    Visitor *v;
    q_obj_xen_set_global_dirty_log_arg arg = {0};

    v = qmp_input_get_visitor(qiv);
    visit_type_q_obj_xen_set_global_dirty_log_arg_members(v, &arg, &err);
    if (err) {
        goto out;
    }

    qmp_xen_set_global_dirty_log(arg.enable, &err);

out:
    error_propagate(errp, err);
    qmp_input_visitor_cleanup(qiv);
    qdv = qapi_dealloc_visitor_new();
    v = qapi_dealloc_get_visitor(qdv);
    visit_type_q_obj_xen_set_global_dirty_log_arg_members(v, &arg, NULL);
    qapi_dealloc_visitor_cleanup(qdv);
}
