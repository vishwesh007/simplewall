#pragma once

// Small overload-style helpers so app code can pass optional section arguments
// while linking against the existing routine API.
#define R_SHIM_OVERLOAD4(_1,_2,_3,_4,NAME,...) NAME
#define R_SHIM_OVERLOAD3(_1,_2,_3,NAME,...) NAME
#define R_SHIM_OVERLOAD2(_1,_2,NAME,...) NAME

static __forceinline BOOLEAN rshim_config_getboolean2(LPCWSTR key_name, BOOLEAN def_value)
{
    return _r_config_getboolean(key_name, def_value);
}

static __forceinline BOOLEAN rshim_config_getboolean3(LPCWSTR key_name, BOOLEAN def_value, LPCWSTR section_name)
{
    return _r_config_getboolean_ex(key_name, def_value, section_name);
}

#define _r_config_getboolean(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getboolean3, rshim_config_getboolean2)(__VA_ARGS__)

static __forceinline LONG rshim_config_getlong2(LPCWSTR key_name, LONG def_value)
{
    return _r_config_getlong(key_name, def_value);
}

static __forceinline LONG rshim_config_getlong3(LPCWSTR key_name, LONG def_value, LPCWSTR section_name)
{
    return _r_config_getlong_ex(key_name, def_value, section_name);
}

#define _r_config_getlong(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getlong3, rshim_config_getlong2)(__VA_ARGS__)

static __forceinline LONG64 rshim_config_getlong642(LPCWSTR key_name, LONG64 def_value)
{
    return _r_config_getlong64(key_name, def_value);
}

static __forceinline LONG64 rshim_config_getlong643(LPCWSTR key_name, LONG64 def_value, LPCWSTR section_name)
{
    return _r_config_getlong64_ex(key_name, def_value, section_name);
}

#define _r_config_getlong64(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getlong643, rshim_config_getlong642)(__VA_ARGS__)

static __forceinline ULONG rshim_config_getulong2(LPCWSTR key_name, ULONG def_value)
{
    return _r_config_getulong(key_name, def_value);
}

static __forceinline ULONG rshim_config_getulong3(LPCWSTR key_name, ULONG def_value, LPCWSTR section_name)
{
    return _r_config_getulong_ex(key_name, def_value, section_name);
}

#define _r_config_getulong(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getulong3, rshim_config_getulong2)(__VA_ARGS__)

static __forceinline ULONG64 rshim_config_getulong642(LPCWSTR key_name, ULONG64 def_value)
{
    return _r_config_getulong64(key_name, def_value);
}

static __forceinline ULONG64 rshim_config_getulong643(LPCWSTR key_name, ULONG64 def_value, LPCWSTR section_name)
{
    return _r_config_getulong64_ex(key_name, def_value, section_name);
}

#define _r_config_getulong64(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getulong643, rshim_config_getulong642)(__VA_ARGS__)

static __forceinline PR_STRING rshim_config_getstringexpand2(LPCWSTR key_name, LPCWSTR def_value)
{
    return _r_config_getstringexpand(key_name, def_value);
}

static __forceinline PR_STRING rshim_config_getstringexpand3(LPCWSTR key_name, LPCWSTR def_value, LPCWSTR section_name)
{
    return _r_config_getstringexpand_ex(key_name, def_value, section_name);
}

#define _r_config_getstringexpand(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getstringexpand3, rshim_config_getstringexpand2)(__VA_ARGS__)

static __forceinline PR_STRING rshim_config_getstring2(LPCWSTR key_name, LPCWSTR def_value)
{
    return _r_config_getstring(key_name, def_value);
}

static __forceinline PR_STRING rshim_config_getstring3(LPCWSTR key_name, LPCWSTR def_value, LPCWSTR section_name)
{
    return _r_config_getstring_ex(key_name, def_value, section_name);
}

#define _r_config_getstring(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_getstring3, rshim_config_getstring2)(__VA_ARGS__)

static __forceinline VOID rshim_config_setboolean2(LPCWSTR key_name, BOOLEAN value)
{
    _r_config_setboolean(key_name, value);
}

static __forceinline VOID rshim_config_setboolean3(LPCWSTR key_name, BOOLEAN value, LPCWSTR section_name)
{
    _r_config_setboolean_ex(key_name, value, section_name);
}

#define _r_config_setboolean(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setboolean3, rshim_config_setboolean2)(__VA_ARGS__)

static __forceinline VOID rshim_config_setlong2(LPCWSTR key_name, LONG value)
{
    _r_config_setlong(key_name, value);
}

static __forceinline VOID rshim_config_setlong3(LPCWSTR key_name, LONG value, LPCWSTR section_name)
{
    _r_config_setlong_ex(key_name, value, section_name);
}

#define _r_config_setlong(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setlong3, rshim_config_setlong2)(__VA_ARGS__)

static __forceinline VOID rshim_config_setlong642(LPCWSTR key_name, LONG64 value)
{
    _r_config_setlong64(key_name, value);
}

static __forceinline VOID rshim_config_setlong643(LPCWSTR key_name, LONG64 value, LPCWSTR section_name)
{
    _r_config_setlong64_ex(key_name, value, section_name);
}

#define _r_config_setlong64(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setlong643, rshim_config_setlong642)(__VA_ARGS__)

static __forceinline VOID rshim_config_setulong2(LPCWSTR key_name, ULONG value)
{
    _r_config_setulong(key_name, value);
}

static __forceinline VOID rshim_config_setulong3(LPCWSTR key_name, ULONG value, LPCWSTR section_name)
{
    _r_config_setulong_ex(key_name, value, section_name);
}

#define _r_config_setulong(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setulong3, rshim_config_setulong2)(__VA_ARGS__)

static __forceinline VOID rshim_config_setulong642(LPCWSTR key_name, ULONG64 value)
{
    _r_config_setulong64(key_name, value);
}

static __forceinline VOID rshim_config_setulong643(LPCWSTR key_name, ULONG64 value, LPCWSTR section_name)
{
    _r_config_setulong64_ex(key_name, value, section_name);
}

#define _r_config_setulong64(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setulong643, rshim_config_setulong642)(__VA_ARGS__)

static __forceinline VOID rshim_config_setstringexpand2(LPCWSTR key_name, LPWSTR value)
{
    _r_config_setstringexpand(key_name, value);
}

static __forceinline VOID rshim_config_setstringexpand3(LPCWSTR key_name, LPWSTR value, LPCWSTR section_name)
{
    _r_config_setstringexpand_ex(key_name, value, section_name);
}

#define _r_config_setstringexpand(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setstringexpand3, rshim_config_setstringexpand2)(__VA_ARGS__)

static __forceinline VOID rshim_config_setstring2(LPCWSTR key_name, LPCWSTR value)
{
    _r_config_setstring(key_name, value);
}

static __forceinline VOID rshim_config_setstring3(LPCWSTR key_name, LPCWSTR value, LPCWSTR section_name)
{
    _r_config_setstring_ex(key_name, value, section_name);
}

#define _r_config_setstring(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_config_setstring3, rshim_config_setstring2)(__VA_ARGS__)

static __forceinline VOID rshim_config_getfont3(LPCWSTR key_name, PLOGFONT logfont, LONG dpi_value)
{
    _r_config_getfont(key_name, logfont, dpi_value);
}

static __forceinline VOID rshim_config_getfont4(LPCWSTR key_name, PLOGFONT logfont, LONG dpi_value, LPCWSTR section_name)
{
    _r_config_getfont_ex(key_name, logfont, dpi_value, section_name);
}

#define _r_config_getfont(...) R_SHIM_OVERLOAD4(__VA_ARGS__, rshim_config_getfont4, rshim_config_getfont3)(__VA_ARGS__)

static __forceinline VOID rshim_config_setfont3(LPCWSTR key_name, PLOGFONT logfont, LONG dpi_value)
{
    _r_config_setfont(key_name, logfont, dpi_value);
}

static __forceinline VOID rshim_config_setfont4(LPCWSTR key_name, PLOGFONT logfont, LONG dpi_value, LPCWSTR section_name)
{
    _r_config_setfont_ex(key_name, logfont, dpi_value, section_name);
}

#define _r_config_setfont(...) R_SHIM_OVERLOAD4(__VA_ARGS__, rshim_config_setfont4, rshim_config_setfont3)(__VA_ARGS__)

static __forceinline VOID rshim_obj_addlistitem2(PR_LIST list_node, PVOID list_item)
{
    _r_obj_addlistitem(list_node, list_item);
}

static __forceinline VOID rshim_obj_addlistitem3(PR_LIST list_node, PVOID list_item, PULONG_PTR new_index_ptr)
{
    _r_obj_addlistitem_ex(list_node, list_item, new_index_ptr);
}

#define _r_obj_addlistitem(...) R_SHIM_OVERLOAD3(__VA_ARGS__, rshim_obj_addlistitem3, rshim_obj_addlistitem2)(__VA_ARGS__)

static __forceinline VOID rshim_theme_initialize2(HWND hwnd, BOOLEAN is_enable)
{
    _r_theme_initialize(hwnd, is_enable);
}

static __forceinline VOID rshim_theme_initialize1(HWND hwnd)
{
    _r_theme_initialize(hwnd, _r_theme_isenabled());
}

#define _r_theme_initialize(...) R_SHIM_OVERLOAD2(__VA_ARGS__, rshim_theme_initialize2, rshim_theme_initialize1)(__VA_ARGS__)

// Older call sites pass string refs and numeric PIDs or use legacy parameter ordering.
// Adapt them to the current routine API.

#define rshim_str_gethash_impl _r_str_gethash
static __forceinline ULONG rshim_str_gethash_ref(const R_STRINGREF *string, BOOLEAN is_ignorecase)
{
    return _r_str_gethash2((PR_STRINGREF)string, is_ignorecase);
}
static __forceinline ULONG rshim_str_gethash_wstr(LPCWSTR string, BOOLEAN is_ignorecase)
{
    return rshim_str_gethash_impl((LPWSTR)string, is_ignorecase);
}
#define _r_str_gethash(str, ignorecase) _Generic((str), \
    const R_STRINGREF *: rshim_str_gethash_ref, \
    R_STRINGREF *: rshim_str_gethash_ref, \
    default: rshim_str_gethash_wstr \
)((str), (ignorecase))

#define rshim_path_geticon_impl _r_path_geticon
static __forceinline BOOLEAN rshim_path_geticon(const R_STRINGREF *path, HICON_PTR out_hicon, PLONG out_icon_id)
{
    return rshim_path_geticon_impl((PR_STRINGREF)path, out_icon_id, out_hicon);
}
#define _r_path_geticon(path, out_icon_id, out_hicon) rshim_path_geticon((path), (out_icon_id), (out_hicon))

#define rshim_sys_openprocess_impl _r_sys_openprocess
static __forceinline NTSTATUS rshim_sys_openprocess_any(ULONG_PTR process_id, ACCESS_MASK desired_access, PHANDLE out_buffer)
{
    return rshim_sys_openprocess_impl((HANDLE)process_id, desired_access, out_buffer);
}
#define _r_sys_openprocess(process_id, desired_access, out_buffer) rshim_sys_openprocess_any((ULONG_PTR)(process_id), (desired_access), (out_buffer))

#define rshim_sys_querytaginformation_impl _r_sys_querytaginformation
static __forceinline PR_STRING rshim_sys_querytaginformation_any(ULONG_PTR hprocess, LPCVOID tag)
{
    return rshim_sys_querytaginformation_impl((HANDLE)hprocess, tag);
}
#define _r_sys_querytaginformation(hprocess, tag) rshim_sys_querytaginformation_any((ULONG_PTR)(hprocess), (tag))

static __forceinline NTSTATUS _r_sys_terminateprocess(HANDLE process_handle, NTSTATUS exit_status)
{
    return NtTerminateProcess(process_handle, exit_status);
}

#define rshim_wnd_adjustrectangletoworkingarea_impl _r_wnd_adjustrectangletoworkingarea
static __forceinline VOID rshim_wnd_adjustrectangletoworkingarea(PR_RECTANGLE rectangle, HWND hwnd)
{
    rshim_wnd_adjustrectangletoworkingarea_impl(rectangle, hwnd);
}
#define _r_wnd_adjustrectangletoworkingarea(hwnd, rectangle) rshim_wnd_adjustrectangletoworkingarea((rectangle), (hwnd))

#define rshim_ctrl_setselection_impl _r_ctrl_setselection
static __forceinline VOID rshim_ctrl_setselection3(HWND hwnd, INT ctrl_id, LONG_PTR pos)
{
    rshim_ctrl_setselection_impl(hwnd, ctrl_id, pos);
}
static __forceinline VOID rshim_ctrl_setselection4(HWND hwnd, INT ctrl_id, LONG_PTR start, LONG_PTR end)
{
    rshim_ctrl_setselection_impl(hwnd, ctrl_id, MAKELPARAM(start, end));
}
#define _r_ctrl_setselection(...) R_SHIM_OVERLOAD4(__VA_ARGS__, rshim_ctrl_setselection4, rshim_ctrl_setselection3)(__VA_ARGS__)

#define _r_menu_addseparator(hmenu) _r_menu_additem((hmenu), 0, NULL)

// Thread and dialog helpers for signature mismatches
static __forceinline NTSTATUS rshim_sys_createthread(PHANDLE thread_handle, HANDLE process_handle, PVOID start_address, PVOID parameter, PR_ENVIRONMENT environment, LPCWSTR description)
{
    return _r_sys_createthread(thread_handle, process_handle, (PUSER_THREAD_START_ROUTINE)start_address, parameter, environment, description);
}
#define _r_sys_createthread(...) rshim_sys_createthread(__VA_ARGS__)

static __forceinline VOID rshim_filedialog_setpath(PR_FILE_DIALOG file_dialog, const R_STRINGREF *path_sr)
{
    _r_filedialog_setpath(file_dialog, (LPWSTR)path_sr->buffer);
}
#define _r_filedialog_setpath(dlg, path_sr) rshim_filedialog_setpath((dlg), (path_sr))
