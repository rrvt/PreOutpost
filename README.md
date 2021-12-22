# PreOutpost

Supplies profiles for all BBSes among other services.  With a selection from a toolbar dropdown list and
a twist of a knob on the radio the user may change BBSes.  A Subject Line may be produced and sent to the
clipboard for subsequent pasting into a subject line or other location in a form.  The complete personal
and tactical information may be entered once and sent to all BBS profiles with this application.

The complete address book is displayed in a sister window (note scrolling may be necessary).  The address
name and text that the name represents is shown.  Additional addresses may be created.  The PDF files that
describe where messages should be sent is available from one of the menu items (Routing) and a pdf Routing
Slip is also available.

## Getting Started

The Windows PreOutpostInstaller.msi file will install the program.  At this time only one version of
PreOutpost is produced.  It should run on Win7, 8 and 10.

A help file is included.  Let the author know if the help file needs improving...

## Updates

### Update 12/21/21

While creating a template for a dialog box only application with a toolbar the Library was added to and
changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons, edit boxes,
combo boxes and drop down menus as well as the traditional 16x15 icons.

PreOutpost is a Dialog App and does not have any toolbars at this time.

Also trimmed some of the unneeded MFC windows code from the InitInstance functions in both applications.

### Update 11/15/21

Apparently CWinAppEx intializes the Shell Manager and CWinApp does not.  To get some functionality in
CApp I based the OPaddress app on CApp instead of CWinApp.  Go figure.  In this case
the change caused the OPaddress app to abort when it tried to initalize the Shell Manager twice.
Removed two lines to fix the problem.

### Update 11/13/21

But the major changes are in the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation smaller,
also fixed one bug (or feature) in the ExpandableP insert sorted function that would throw out entries
that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function to
get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in the
About Box code.  Some other library changes.  Some corresponding changes in the application.

### Update 2/9/21

The Library has changed to accomodate RWracesDB and CodeGen, however more extensive changes to the
directory structure of this application were made to bring it in line with other applications on my
system.  Also, while older OSes were supported by this application in the past, Outpost itself has
moved away from OS's lower than Win7.  Thus those compilations were sidelined and now there is just
one version.

### Update 9/10/20

Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### August 22, 2020

Tried to update the profile suffixes and discovered a lingering Unicode bug.  Of course it was a couple of
days before I found the bug.  It has been a few years since I wrote this program and when I went looking
for the bug I was unhappy with the organization of the program.  So I embarked on a refactoring effort and
whenever an extensive change is made every command must be examined closely to verify the correct
functionality.  Eventually this led to finding a few characters that were not enclosed with the "_T('')"
Unicode/Ansi macro.  Attacked the OPaddress application with the same idea in mind.

The OPaddress application had not been touched since before the last Outpost update.  It turns out that
the feature to find hidden actual addresses by analysing the transaction log was no longer working due
to changes in the form handling.  Added a finite state machine with regular expressions to pick out
significant lines in the log and then sanitize the virtual address (all upper case and
only letters, digits, period and underscore) and save the data in the address book.  Note to self, look
at the address book when the next Outpost is released.

### August 16, 2020

Mostly internal changes, but it should be noted that the installer puts the PreOutpost program directory
on the system path so that in the Dos Box (Command Prompt, Take Command, etc.) the command line will
respond to "PreOutpost" regardless of the current directory.  This should be helpful when creating a
master file.  Of course what works on one operating system may not work on another, so one might be
required to changed directories to the PreOutpost directory in the Program Files.

## Built With

Slickedit is used for all edits, Visual Studio 2017 with various additions (Wix being one) is used to
build and debug.  The old fashion Help Workshop is used to compile the help file and an old copy of
Dreamweaver is used to construct the html files used in the Help Workshop.

This work originally supported Win2K, WinXp, Win7 Ansi and Unicode.  The Outpost authors have announced
that they will no longer support operating systems older than Win7.  For a variety of reasons have stop
supporting the Ansi character set and thus the current version is written using the Unicode character
set.

My current operating system is Windows 7 and I have little interest in moving to Windows 10 until it
appears to be stable.  In April 2020 it does not appear stable.

## Authors

Robert R. Van Tuyl, K6RWY, romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License.

## Acknowledgments

The Authors of Outpost did (and maintaining) an incredible jobs creating the software.  The members of
the Santa Clara County Radio Amateur Civil Emergency Service built and maintain several BBSes of which 4
are on top of buildings or mountains in or near the Santa Clara County, California.

