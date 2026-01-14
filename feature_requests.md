## ✅ IMPLEMENTED: Automatic Firewall Hardening Based on Timestamps

**Original Request:**
> please add automatic firewall hardening based on timestamps ,that is block should be able to be scheduled for example after 12 all connections are killed till 7 next morning ,this is example user can add any timelines please

**Implementation:**
This feature has been implemented with the following functionality:

### Features Added:
1. **Settings Page** - New "Schedule" settings page under Settings menu
   - Enable/disable scheduled blocking checkbox
   - Configurable start time (hour:minute)
   - Configurable end time (hour:minute)
   - Status display showing current schedule state

2. **Tray Menu Toggle** - Quick toggle in system tray context menu
   - "Scheduled Blocking" checkbox item for fast enable/disable

3. **Automatic Time-based Blocking**
   - When enabled, firewall will automatically block ALL connections during the scheduled time
   - Works across midnight (e.g., 23:00 to 07:00)
   - Uses Windows threadpool timers for efficient scheduling
   - Automatically reschedules for the next event

4. **Notifications**
   - Tray popup when scheduled blocking activates
   - Tray popup when scheduled blocking deactivates

### Default Settings:
- Schedule Start: 00:00 (midnight)
- Schedule End: 07:00 (7 AM)

### Files Modified:
- `src/resource.h` - Added new control and string IDs
- `src/main.h` - Added schedule timer and state to STATIC_DATA
- `src/timer.h` - Added schedule function declarations
- `src/timer.c` - Implemented schedule logic
- `src/main.c` - Added settings page initialization and command handling
- `src/messages.c` - Added tray menu item for schedule toggle
