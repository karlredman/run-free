//run-free.cc

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <stdio.h>		// sprintf
#include <stdlib.h>		// for system 
#include <assert.h>		// for assert
#include <string.h>		// for memset
#include <unistd.h>		// fork
#include <errno.h>

#include "run-free.h"

extern void freeHistoryList(GList *h);
extern int historyInit(GList *cbItems);
extern int writeHistory(char *s);
void fileOK(GtkWidget *widget, gpointer data);
gboolean fileDialog_delete_handler(GtkWidget *widget, GdkEvent *event,
				   gpointer user_data);
void fileDialog_keyPress(GtkWidget *widget, GdkEventKey *event, gpointer *data);

void runClicked(GtkWidget *widget, gpointer data);


/* GLOBALS */
int fileDialogUp =	0;	/* alows one instance of file dialog */
int use_history =	1;	/* use history ? */
int *run_in_term =	NULL;	/* run in a terminal */
GList *historyList;

extern char **environ;		/* the environment */

/* BUTTONS */
GtkWidget	*combo;		// the combo box
GtkWidget	*runButton;	/* the run button */
GtkWidget	*cancelButton;	/* the cancel button */
GtkWidget	*checkButton;	// (for run_in_terminal selection)
GtkWidget	*browseButton;	// (for visual file selection)

int cleanUp()
{
  //close files and handle history
  freeHistoryList(historyList);
  return 0;
}


int my_system(const char *command)
{
  /* performes a system call like systemi().  This is the recomended
     method in the linux man pages; besides, I wasn't sure if I would
     need this down the line -so I added it anyway
  */
  int pid;

  if(command == 0)
    return 1;

  pid = fork();
  if(pid == -1)
    return -1;
  if(pid == 0)
    {
      char * argv[4];
      argv[0] = "sh";
      argv[1] = "-c";
      argv[2] = (char *)command;
      argv[3] = 0;

#ifdef DEBUG
	g_print("my_system: running command: %s %s %s\n", argv[0], argv[1], argv[2]);
#endif

      execve("/bin/sh", argv, environ);
      exit(127);
    }
  return 0;
}


void combo_keyPress(GtkWidget *widget, GdkEventKey *event, gpointer *data)
{
  /* 
     trap key presses in the combo box
  */
  static unsigned int prevKey =0;

  if(event->keyval == GDK_Return) // run
    {
      //run the command
      gtk_button_clicked(GTK_BUTTON(runButton));
    }    
  else if(event->keyval == GDK_Escape) // quit
    {
      //cancel operations
      gtk_button_clicked(GTK_BUTTON(cancelButton));
    }
  else if(event->keyval == GDK_t) // run_in_term toggle
    {
      if(prevKey == GDK_Control_L || prevKey == GDK_Control_R)
	  gtk_button_clicked(GTK_BUTTON(checkButton));
    }
  else if(event->keyval == GDK_b) // brows accel
    {
      
      if( (prevKey == GDK_Control_L || prevKey == GDK_Control_R) && ! fileDialogUp)
	  gtk_button_clicked(GTK_BUTTON(browseButton));
    }
  else if(event->keyval == GDK_downarrow)
    {
#ifdef DEBUG
      g_print("%s\n",data);
#endif
    }
  else
    if(event->keyval == GDK_Control_L || event->keyval == GDK_Control_R)
      prevKey = event->keyval;
    else
      prevKey = 0;
}

gint closeAppWindow(GtkWidget *widget, gpointer gdata)
{
  /*
    clean up and shutdown
  */

  cleanUp();

  //send a quit message
   gtk_main_quit();

  //ok to be closed. TRUE would prevent window 
  //from closing
  return (FALSE);
}

void comboFunc(GtkWidget *widget, gpointer data)
{
  //notified when the combo entry was changed
  // -not neccessary

#ifdef DEBUG  
  g_print("combo changed\n");
#endif

  return;
} 


void runClicked(GtkWidget *widget, gpointer data)
{
  /* execute the command line.  Formats the command line and executes
     it using my_system()
  */

  char *s;
  char *commandLine;
  int retval = 0;

  //get the entry field from the combo and set it to a local var
  s = gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(data)->entry));

if(s)
  {
    //set exec command
    char *begExCommand = "sh -c ' ";// pre
    char *endExCommand = " ' &"; // post

    //get string lengths
    int beLen = strlen(begExCommand);
    int eeLen = strlen(endExCommand);
    int sLen = strlen(s);

    //calculate the commandLine Length
    int cLen = sLen+beLen+eeLen;


  //check if "run in term" toggled and
  //execute program & check for error
  if(*run_in_term == 1)
    {
      char *t = "-e";

      //create a commandLine array
      commandLine = new char[strlen(TERM) +strlen(RF_RUN_IN_TERM_NAME)
			    +strlen(t) +1];
      memset(commandLine, 0, sizeof(*commandLine));

      //format commandLine
      sprintf(commandLine, "%s %s %s", TERM, t, RF_RUN_IN_TERM_NAME);

      //make script to run in terminal
      if(createScript(s) != 0)
	{
	  //display error message
	  
	  #ifdef DEBUG
	  g_print("createScript() FAILED\n");
	  #endif

	  cleanUp();
	  gtk_main_quit();
	}
    }
  else
    {
      //create a commandLine array
      commandLine = new char[cLen];
      memset(commandLine, '0', sizeof(*commandLine));

      //copy the formated peices into the commandLine
      memcpy(&commandLine[0], begExCommand, beLen);
      memcpy(&commandLine[beLen], s, sLen);
      memcpy(&commandLine[beLen+sLen], endExCommand, eeLen);

      commandLine[cLen] = '\0';
    }

#ifdef DEBUG
      g_print("\n");
      g_print("\n");
      g_print(commandLine);
      g_print("\n");
#endif

  //run commandline
  my_system(commandLine);

  //do cleanup and exit
  if(strlen(s) > 0)
    {
      writeHistory(s);		// save history

      if(retval = -1)
	{
	  
	}

      cleanUp();		// clean up
      if (commandLine != NULL)	// delete commandLine
	delete [] commandLine;
      gtk_main_quit();		// quit 
    }
  }
  return;
}



void cancelClicked(GtkWidget *widget, gpointer data)
{
  //do cleanup
  cleanUp();

  //terminate
  gtk_main_quit();
}

void checkClicked(GtkWidget *widget, gpointer data)
{
  /* toggle the run_in_term variable */

  assert(run_in_term);

  if(*run_in_term)
    *run_in_term = 0;
  else
    *run_in_term = 1;
}


void browseClicked(GtkWidget *widget, gpointer data)
{
  if(fileDialogUp == 1)
    return;

  GtkWidget *fDialog;

  fDialog = gtk_file_selection_new("run program");

  //destroy the object if cancel is pressed
  gtk_signal_connect_object( GTK_OBJECT (GTK_FILE_SELECTION(fDialog)->cancel_button),
			     "clicked",
			     (GtkSignalFunc)gtk_widget_destroy,
			     GTK_OBJECT (fDialog));

  //set the callback if the ok button is pressed
  gtk_signal_connect( GTK_OBJECT (GTK_FILE_SELECTION(fDialog)->ok_button),
			     "clicked", GTK_SIGNAL_FUNC(fileOK),
			     fDialog);
  
  gtk_signal_connect(GTK_OBJECT (GTK_FILE_SELECTION(fDialog)), "key_press_event",
		     GTK_SIGNAL_FUNC(fileDialog_keyPress), fDialog);


  gtk_signal_connect( GTK_OBJECT (GTK_FILE_SELECTION(fDialog)),
			     "delete_event",
		      GTK_SIGNAL_FUNC(fileDialog_delete_handler),
			     NULL);

  //show dialog
  fileDialogUp = 1;
  gtk_widget_show(fDialog);

  return;
}



int main(int argc, char **argv, char **e)
{
  //################# objects & variables
  //# the main window
  GtkWidget *dialog;

  //# a table group (for combo and browse btn placement)
  GtkWidget *table;

  //# combo box stuff (for the command line)
  GList *cbitems = NULL;
  GtkEntry *entry = NULL;

  //run_in_terminal decision
  run_in_term = new int;
  *run_in_term = 0;


  //################# main window

  //Initialize gtk, handle GTK command line parameters
  gtk_init(&argc, &argv);

  //create the main window -a dialog box
  dialog = gtk_dialog_new();

  //call closeAppWindow when the window gets a "delete_event" signal
  gtk_signal_connect(GTK_OBJECT(dialog), "delete_event",
		     GTK_SIGNAL_FUNC(closeAppWindow), NULL);

  //set the main window's title
  gtk_window_set_title(GTK_WINDOW (dialog), RF_MWINDOW_TITLE);

  //set the border width for the main window
  gtk_container_border_width(GTK_CONTAINER (dialog), RF_MWINDOW_BORDERWIDTH);


  //################## group table
  /*
    NOTE: I picked the number of table elements at arbitrarily.  I wasn't
    sure how this would effect the look of this app on other hardware,
    etc. either.  
    This table is set inside the default table within the dialog box's
    label/text area.
  */
  ////add the combo to the dialog's vbox area within an table
  table = gtk_table_new(1, 51, TRUE);	/* horizontal box */


  //################# combo box
  
  //create a list for the combo box
  cbitems = g_list_append(cbitems, (void *)""); //first item (shows) blank
  
  //initialize history list
  historyInit(cbitems);
  
  //create the combo box
  combo = gtk_combo_new();

  //create the drop-down portion
  gtk_combo_set_popdown_strings(GTK_COMBO(combo), cbitems);

  //get the entry field of the combo box (for later use)
  entry = GTK_ENTRY(GTK_COMBO(combo)->entry);

  //set a callback for combo box changed events
  gtk_signal_connect(GTK_OBJECT (GTK_COMBO (combo)->entry), "changed",
		     GTK_SIGNAL_FUNC(comboFunc), NULL);
  
  //set a callback for key_press events
  /*
    amoungst other things the callback will handle an 'ENTER' press
    and an 'ESC' press.
  */    
  gtk_signal_connect(GTK_OBJECT (dialog), "key_press_event",
		     GTK_SIGNAL_FUNC(combo_keyPress), combo);

  //set the combo box in the table
  /*
    the combo box will span table items 0 through 40 and be 1 row
     high.  This is based on the arbitrary table width i used earlier
  */
  gtk_table_attach(GTK_TABLE(table), combo, 0, 40, 0, 1,
    (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), 0,0);
	
  //set the table in the diagog's vbox
  gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->vbox), table,
		       TRUE, TRUE, 0);

  //show widget
  gtk_widget_show(combo);

  //############################ browseButton
  //create a button
  browseButton = gtk_button_new_with_label("Browse");
  
  //give the button an event handler
  /*
    intended to add "browse" functionality to select the program to
    execute -brings up a file-dialog box
  */
  gtk_signal_connect(GTK_OBJECT(browseButton), "clicked",
		     GTK_SIGNAL_FUNC(browseClicked), NULL);
  
  //add button to table->vbox in dialog
  /*
    spans table elements 41 through 51 (spacing out the button and the
    combo box. the button is the same hieght as the combo box
  */
  gtk_table_attach(GTK_TABLE(table), browseButton, 41, 51, 0, 1,
		   (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), 
		   (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), 0, 0);

  //show the widget
  gtk_widget_show(browseButton);

  
  //############################ checkbox
  //create a button
  checkButton = gtk_check_button_new_with_label("run in terminal");
  
  //give the button an event handler
  /*
    this will allow the command line to be executed in a terminal from
    a temporary shell script. the callback uses the run_in_term int
    pointer we initialized earlier.
  */
  gtk_signal_connect(GTK_OBJECT(checkButton), "clicked",
		     GTK_SIGNAL_FUNC(checkClicked), NULL);

  //add button to dialog's action area
  gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->action_area), checkButton,
		       TRUE, TRUE, 0);

  //show the widget
  gtk_widget_show(checkButton);

  //############################ runButton
  //create a button
  runButton = gtk_button_new_with_label(" Run ");
  
  //give the button an event handler
  /*
    clicking this button will execute the commandLine entered in the
    combo box
  */
 gtk_signal_connect(GTK_OBJECT(runButton), "clicked",
		     GTK_SIGNAL_FUNC(runClicked),
		     combo);

  //add button to dialog's action area
  gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->action_area), runButton,
		       TRUE, TRUE, 0);

  //show the widget
  gtk_widget_show(runButton);

  //############################ cancelButton
  //create a button
  cancelButton = gtk_button_new_with_label("Cancel");
  
  //give the button an event handler -it'll call the function
  gtk_signal_connect(GTK_OBJECT(cancelButton), "clicked",
		     GTK_SIGNAL_FUNC(cancelClicked), NULL);
  
  //add button to the dialog's action area
  gtk_box_pack_start(GTK_BOX (GTK_DIALOG (dialog)->action_area),
		     cancelButton, TRUE, TRUE, 0);

  //show the widget
  gtk_widget_show(cancelButton);


  //######################## show windows
  //make top-level window visible
  gtk_widget_show(table);
  gtk_widget_show(dialog);

  //set the initial focus on the entry portion of the combo box
  gtk_window_set_focus(GTK_WINDOW(dialog),
		       GTK_WIDGET(GTK_ENTRY(GTK_COMBO(combo)->entry)));

  //main event loop int gtk.  We have no event handlers though!
  gtk_main();

  //clean up
  delete run_in_term;
 
  return 0;
}


void fileOK(GtkWidget *widget, gpointer data)
{
  /* handle a file dialog's OK button click */
  char *sTempFile;

  //typFileSelectionData *localdata;
  //GtkWidget *filew;

    sTempFile =
      gtk_file_selection_get_filename(GTK_FILE_SELECTION(data));


    if(sTempFile[strlen(sTempFile)-1] == '/')
      {
	// if its a directory, lets stay here and wait for input
	gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget->parent->parent->parent),sTempFile);
      }
    else
      {
	//add fileselection to combo entry field
	gtk_entry_set_text(GTK_ENTRY( GTK_COMBO(combo)->entry), sTempFile);

	//destroy the filedialog
	gtk_widget_destroy(widget->parent->parent->parent);
      }
}

gboolean fileDialog_delete_handler(GtkWidget *widget, GdkEvent *event,
				   gpointer user_data)
{
  fileDialogUp = 0;
  return(FALSE);
}

void fileDialog_keyPress(GtkWidget *widget, GdkEventKey *event, gpointer *data)
{
  /* 
     trap key presses in the combo box
  */
  static unsigned int prevKey =0;

  //g_print("fileDialog_keyPress\n");
  
  if(event->keyval == GDK_Escape) // quit
    {
      //cancel operations
      gtk_button_clicked(GTK_BUTTON(GTK_FILE_SELECTION(widget)->cancel_button));
      fileDialogUp=0;
    }
  else if(event->keyval == GDK_t) // run_in_term toggle
    {
      if(prevKey == GDK_Control_L || prevKey == GDK_Control_R)
	gtk_button_clicked(GTK_BUTTON(checkButton));
    }
  else
    if(event->keyval == GDK_Control_L || event->keyval == GDK_Control_R)
      prevKey = event->keyval;
    else
      prevKey = 0;
}
