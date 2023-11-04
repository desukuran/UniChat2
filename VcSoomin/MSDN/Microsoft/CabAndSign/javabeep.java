//******************************************************************************
// javabeep.java:	Applet
//
//	This applet is a simple demonstration of calling a COM object in a
//	Java program, utilizing the ActiveX runtime for Java. The COM object 
//  is the Beeper sample from the ActiveX Template Library (ATL). ATL is 
//	a Template based Visual C++ 4.x add on that contains a custom AppWizard 
//	and various header files to generate a skeleton ActiveX Control. For 
//	more information on ATL, including the source code to the beeper.dll 
//	COM object, please visit the Microsoft web site at:
//
//					http://www.microsoft.com/visualc/v42/atl
//
//	Most of the code of interest can be found in the javabeep.mouseDown 
//	and javabeep.start methods
//******************************************************************************
import java.applet.*;
import java.awt.*;
import javabeepframe;

// Import the class files that JavaTLB generates from beeper.dll
import beeper.*;

//==============================================================================
// Main Class for applet javabeep
//
//==============================================================================
public class javabeep extends Applet implements Runnable
{
	// Beeper COM Interface variable
	IBeeper m_Beeper=null;

	// THREAD SUPPORT:
	//		m_javabeep	is the Thread object for the applet
	//--------------------------------------------------------------------------
	Thread	 m_javabeep = null;

	// ANIMATION SUPPORT:
	//		m_Graphics		used for storing the applet's Graphics context
	//		m_Images[]		the array of Image objects for the animation
	//		m_nCurrImage	the index of the next image to be displayed
	//		m_ImgWidth		width of each image
	//		m_ImgHeight		height of each image
	//		m_fAllLoaded	indicates whether all images have been loaded
	//		NUM_IMAGES 		number of images used in the animation
	//--------------------------------------------------------------------------
	private Graphics m_Graphics;
	private Image	 m_Images[];
	private int 	 m_nCurrImage;
	private int 	 m_nImgWidth  = 0;
	private int 	 m_nImgHeight = 0;
	private boolean  m_fAllLoaded = false;
	private final int NUM_IMAGES = 18;

	// STANDALONE APPLICATION SUPPORT:
	//		m_fStandAlone will be set to true if applet is run standalone
	//--------------------------------------------------------------------------
	boolean m_fStandAlone = false;

	// STANDALONE APPLICATION SUPPORT
	// 	The main() method acts as the applet's entry point when it is run
	// as a standalone application. It is ignored if the applet is run from
	// within an HTML page.
	//--------------------------------------------------------------------------
	public static void main(String args[])
	{
		// Create Toplevel Window to contain applet javabeep
		//----------------------------------------------------------------------
		javabeepframe frame = new javabeepframe("javabeep");

		// Must show Frame before we size it so insets() will return valid values
		//----------------------------------------------------------------------
		frame.show();
        frame.hide();
		frame.resize(frame.insets().left + frame.insets().right  + 320,
					 frame.insets().top  + frame.insets().bottom + 240);

		// The following code starts the applet running within the frame window.
		// It also calls GetParameters() to retrieve parameter values from the
		// command line, and sets m_fStandAlone to true to prevent init() from
		// trying to get them from the HTML page.
		//----------------------------------------------------------------------
		javabeep applet_javabeep = new javabeep();

		frame.add("Center", applet_javabeep);
		applet_javabeep.m_fStandAlone = true;
		applet_javabeep.init();
		applet_javabeep.start();
        frame.show();
	}

	// javabeep Class Constructor
	//--------------------------------------------------------------------------
	public javabeep()
	{
	}

	// APPLET INFO SUPPORT:
	//		The getAppletInfo() method returns a string describing the applet's
	// author, copyright date, or miscellaneous information.
    //--------------------------------------------------------------------------
	public String getAppletInfo()
	{
		return "Name: javabeep\r\n" +
		       "Author: Stephen Horne\r\n" +
		       "Created with Microsoft Visual J++";
	}


	// The init() method is called by the AWT when an applet is first loaded or
	// reloaded.  Override this method to perform whatever initialization your
	// applet needs, such as initializing data structures, loading images or
	// fonts, creating frame windows, setting the layout manager, or adding UI
	// components.
    //--------------------------------------------------------------------------
	public void init()
	{
        // If you use a ResourceWizard-generated "control creator" class to
        // arrange controls in your applet, you may want to call its
        // CreateControls() method from within this method. Remove the following
        // call to resize() before adding the call to CreateControls();
        // CreateControls() does its own resizing.
        //----------------------------------------------------------------------
		resize(320, 240);

	}

	// Place additional applet clean up code here.  destroy() is called when
	// when you applet is terminating and being unloaded.
	//-------------------------------------------------------------------------
	public void destroy()
	{
	}

    // ANIMATION SUPPORT:
    //		Draws the next image, if all images are currently loaded
    //--------------------------------------------------------------------------
	private void displayImage(Graphics g)
	{
		if (!m_fAllLoaded)
			return;

		// Draw Image in center of applet
		//----------------------------------------------------------------------
		g.drawImage(m_Images[m_nCurrImage],
				   (size().width - m_nImgWidth)   / 2,
				   (size().height - m_nImgHeight) / 2, null);

		// Draw a click me label
		FontMetrics fm = getFontMetrics(getFont());
		String message = new String("Click me with the mouse!");
		g.drawString(message,(size().width-fm.stringWidth(message))/2,				
				     3*(size().height)/4);
	}

	// javabeep Paint Handler
	//--------------------------------------------------------------------------
	public void paint(Graphics g)
	{
		// ANIMATION SUPPORT:
		//		The following code displays a status message until all the
		// images are loaded. Then it calls displayImage to display the current
		// image.
		//----------------------------------------------------------------------
		if (m_fAllLoaded)
		{
			Rectangle r = g.getClipRect();
			
			g.clearRect(r.x, r.y, r.width, r.height);
			displayImage(g);
		}
		else
			g.drawString("Loading images...", 10, 20);

	}

	//		The start() method is called when the page containing the applet
	// first appears on the screen. The AppletWizard's initial implementation
	// of this method starts execution of the applet's thread.
	//--------------------------------------------------------------------------
	public void start()
	{
		if (m_javabeep == null)
		{
			m_javabeep = new Thread(this);
			m_javabeep.start();
		}

		// Create the Beeper object
		m_Beeper = (IBeeper) new Beeper();
	}
	
	//		The stop() method is called when the page containing the applet is
	// no longer on the screen. The AppletWizard's initial implementation of
	// this method stops execution of the applet's thread.
	//--------------------------------------------------------------------------
	public void stop()
	{
		if (m_javabeep != null)
		{
			m_javabeep.stop();
			m_javabeep = null;
		}

	}

	// THREAD SUPPORT
	//		The run() method is called when the applet's thread is started. If
	// your applet performs any ongoing activities without waiting for user
	// input, the code for implementing that behavior typically goes here. For
	// example, for an applet that performs animation, the run() method controls
	// the display of images.
	//--------------------------------------------------------------------------
	public void run()
	{
		m_nCurrImage = 0;
		
		// If re-entering the page, then the images have already been loaded.
		// m_fAllLoaded == TRUE.
		//----------------------------------------------------------------------
        if (!m_fAllLoaded)
		{
    		repaint();
    		m_Graphics = getGraphics();
    		m_Images   = new Image[NUM_IMAGES];

    		// Load in all the images
    		//------------------------------------------------------------------
    		MediaTracker tracker = new MediaTracker(this);
    		String strImage;

    		// For each image in the animation, this method first constructs a
    		// string containing the path to the image file; then it begins
    		// loading the image into the m_Images array.  Note that the call to
    		// getImage will return before the image is completely loaded.
    		//------------------------------------------------------------------
    		for (int i = 1; i <= NUM_IMAGES; i++)
    		{
    			// Build path to next image
    			//--------------------------------------------------------------
    			strImage = "images/img00" + ((i < 10) ? "0" : "") + i + ".gif";
    			if (m_fStandAlone)
    				m_Images[i-1] = Toolkit.getDefaultToolkit().getImage(strImage);
    			else
    				m_Images[i-1] = getImage(getDocumentBase(), strImage);

                tracker.addImage(m_Images[i-1], 0);
    		}

    		// Wait until all images are fully loaded
    		//------------------------------------------------------------------
			try
			{
				tracker.waitForAll();
				m_fAllLoaded = !tracker.isErrorAny();
			}
			catch (InterruptedException e)
			{
			}
			
			if (!m_fAllLoaded)
			{
			    stop();
			    m_Graphics.drawString("Error loading images!", 10, 40);
			    return;
			}
			

			// Assuming all images are same width and height.
			//--------------------------------------------------------------
		    m_nImgWidth  = m_Images[0].getWidth(this);
		    m_nImgHeight = m_Images[0].getHeight(this);
        }		
		repaint();

		while (true)
		{
			try
			{
				// Draw next image in animation
				//--------------------------------------------------------------
				displayImage(m_Graphics);
				m_nCurrImage++;
				if (m_nCurrImage == NUM_IMAGES)
					m_nCurrImage = 0;

				Thread.sleep(50);
			}
			catch (InterruptedException e)
			{
				stop();
			}
		}
	}

	// MOUSE SUPPORT:
	//		The mouseDown() method is called if the mouse button is pressed
	// while the mouse cursor is over the applet's portion of the screen.
	//--------------------------------------------------------------------------
	public boolean mouseDown(Event evt, int x, int y)
	{
		String BeeperString = new String();

		// Call Beeper object 'Beep' method. Note that the Beep object has
		// been written such that on the sixth call to Beep(), the Beep object
		// will return an OLE error code which gets thrown as a Java exception.
		// This sample catches the exception and prints an error message
		try
		{
			m_Beeper.Beep();

			// Call the Beepers getCount and getItem methods
			for(int i=1;i<=m_Beeper.getCount();i++)
			{
				// Build a message string from the strings that getItem returns
				BeeperString+=m_Beeper.getItem(i)+" ";		
			}
		}
		catch(com.ms.com.ComException e)
		{
			// Get the error string
			BeeperString = "Error from Beeper.Beep: handled in mouseDown method";
		}

		// Display the string
		m_Graphics.drawString(BeeperString,x,y);

		return true;
	}

}
