// monad
// For illinois.edu CS 225 spring 2011
// By Jack Toole

#include "monad.h"

namespace monad
{
void find_base_dir(const char * argv0);
void create_mp_part_file();
void processArgs(int argc, const char * const * argv);
void copyRequiredFiles();
void getLibs(const vector<string> & libs);
string updateFolder(const string & folder, bool link);
string getFolder(const string & folder, bool link);
void importFiles(const string & preservedFolder, const string & theSourceFolder,
                 const string & destFolder, const vector<string> & files);
void exec_command(const string & command);

string assignment_base;
int8_t mp_part;
const int8_t no_mp_part = -1;

string testsFolder;
string sourceFolder;
string gradeFolder;
string tempFolder;

FileMap config;

namespace opts
{
bool solution = false;
bool clean    = true;
bool update   = true;
bool staff    = false;
bool newtests = false;
bool provided = false;

bool verbose  = false;
bool buffer   = true;
bool valgrind = false;
bool parallel = false;

bool help     = false;
bool info     = false;
bool license  = false;
#if OPTIMIZE
bool optimize = true;
#else
bool optimize = false;
#endif
}

}

string kyleGetDate() {
	string dateAndTime = "Current Date and Time: ";

	time_t currentTime;
	struct tm * timeStructure;
	time(&currentTime);
	timeStructure = localtime(&currentTime);
	dateAndTime += asctime(timeStructure);

	return dateAndTime;
}



int main(int argc, const char * const * argv)
{
	using namespace monad;

	output::set_error_message();
	
	// Find monad/ directory
	find_base_dir(argv[0]);

	// Read in local config settings.
	// Necessary to do this early for [SVN Root] url
	readConfig("./", config);
	processArgs(argc, argv);

	cout << versioninfo::official_name << endl;
	cout << "Testing " << assignment_base;
	if (mp_part != no_mp_part) cout << '.' << (int)mp_part;
	cout << "..." << endl;
	cout << getRandomQuote() << endl;
	cout << endl;

	cout << "Setting up test environment..." << endl;

	// Read in test-specific config settings
	if (mp_part == no_mp_part)
		readConfig(testsFolder, config);
	else
		readConfig(testsFolder, config, to_string((int)mp_part));

	copyRequiredFiles();

	// Sleep for a second to avoid clock skew warnings
	// This cummulatively adds about 5 minutes to grade each mp,
	// but with the benefit of avoiding newsgroup posts
	// CHANGED: Judging by previous emails, the time needed for
	// this would vary significantly. not sure about solution
	//	sleep(1);

	output::header("Compiling");
	chdir(gradeFolder.c_str());

	// #define MP_PART_NUMBER in proxy
	create_mp_part_file();
	// Change inclusion guards in proxy.h
	exec("sed", "-i", "-e", "s/PROXY_H/PROXY_" + lexical_cast<string>(urand()) + "_H/g", "./proxy.h");

	// run [Pre-Make Commands] config header
	const vector<string> & processing_commands = config["Pre-Make Commands"];
	for (size_t i = 0; i < processing_commands.size(); i++)
		exec_command(processing_commands[i]);

	string makestr = "/usr/bin/make --warn-undefined-variables -Wfatal-errors";
	if (opts::parallel)
		makestr += " --jobs=4";
	if (!opts::verbose)
		makestr += " --quiet";
	if (opts::optimize)
		makestr += " OPTIMIZE=on";
	if (!config["Make Options"].empty())
		makestr += " " + config["Make Options"][0];
	if (opts::verbose)
		cout << makestr <<endl;

	// Compile with make
	system(makestr.c_str()); // yes, system is insecure if the user has control
	                         // over config.ini. But students don't.
							 // TODO (toole1): Yeah but this leaves us open to
							 // aliasing issues, or forces us to specify make's
							 // path. Ugly either way.
	// TODO exec("make", "--quiet", "--warn-undefined-variables", 

	cout << endl << endl;
	vector<string> args;
	if (opts::verbose) args.push_back("--verbose");
	if (opts::valgrind) args.push_back("--valgrind");
	if (!opts::buffer) args.push_back("--noredirect");
	int score = exec("./proxy", args);

	// TODO (toole1): this causes weird output when scores are like 200
	if (score < 0)
	{
		output::header("Running tests");
		cout << "Could not execute test cases" << endl << endl;
		score = 0;

		cout << endl;
		output::total_score(score, -1);
	}

	return score;
}

void monad::create_mp_part_file()
{
	ofstream mp_part_file("mp_part.h");
	mp_part_file << "#ifndef MONAD_SPLIT_LINE_NUMBER" << endl;
	mp_part_file << "#define MONAD_SPLIT_LINE_NUMBER -1" << endl;
	mp_part_file << "#endif" << endl;
	mp_part_file << "#define MONAD_SPLIT (MONAD_SPLIT_LINE_NUMBER == __LINE__ || MONAD_SPLIT_LINE_NUMBER == -1)" << endl;
	mp_part_file << "#define NO_MP_PART " << static_cast<int>(no_mp_part) << endl;
	mp_part_file << "#define MP_PART_NUMBER ";
	if (mp_part == no_mp_part) mp_part_file << "NO_MP_PART"; else mp_part_file << static_cast<int>(mp_part);
	mp_part_file << endl;
	mp_part_file << "#define MP_PART(x) (MP_PART_NUMBER == (x) || MP_PART_NUMBER == NO_MP_PART)" << endl;
	mp_part_file.close();
}

void monad::processArgs(int argc, const char * const * argv)
{
    // Create OptionsMap for options and vector for positional arguments:
	OptionsParser options;

	// Add our possible options to our map
	options.addOption("solution", opts::solution);
	options.addOption("newtests", opts::newtests);
	options.addOption("provided", opts::provided);
	options.addOption("clean",    opts::clean);
	options.addOption("update",   opts::update);
	options.addOption("staff",    opts::staff);
	
	options.addOption("optimize", opts::optimize);
	options.addOption("verbose",  opts::verbose);
	options.addOption("buffer",   opts::buffer);
	options.addOption("valgrind", opts::valgrind);
	options.addOption("parallel", opts::parallel);

	options.addOption("help",     opts::help);
	options.addOption("h",        opts::help);
	options.addOption("info",     opts::info);
	options.addOption("version",  opts::info);
	options.addOption("v",        opts::info);
	options.addOption("license",  opts::license);

	// Add arguments
	string assignment = "";
	options.addArg(assignment);

	// Read in options and arguments
	vector<string> posargs = options.parse(argc, argv);
	
	// Help
	if (opts::help || toLower(assignment) == "help")
	{
		if (toLower(assignment) == "config")
			printHelpConfig();
		else if (toLower(assignment) == "tests")
			printHelpTests();
		else
			printHelp();
		exit(0);
	}

	// Info
	if (opts::info)
	{
		printInfo();
		exit(0);
	}
	
	// License
	if (opts::license)
	{
		printLicense();
		exit(0);
	}
	
	// Clean
	if (toLower(assignment) == "clean")
	{
		system("/bin/rm -rf *_grade/ *_tests/ *_newtests/ *_providedtests *_solution/");
		exit(0);
	}

	// Check argument list length
	if (assignment == "")
	{
		cout << "Usage: " << argv[0] << " mp1" << endl;
		cout << "Run \'" << argv[0] << " --help\' for more information" << endl;
		exit(0);
	}

	// Find mp/lab name and tests folder
	vector<string> splitname = tokenize(assignment, '.');
	assignment_base = splitname[0];
	if (splitname.size() == 1)
		mp_part = no_mp_part;
	else
		mp_part = lexical_cast<int>(splitname[1].c_str());
	
	gradeFolder = "./" + assignment_base + "_grade/";
	if (!exists(gradeFolder)) opts::clean = true;

	if (opts::clean)
		tempFolder = "";
	else
		tempFolder  = "./" + assignment_base + "_temp/";

	// Find source folder (i.e. ../mp1)
	if (opts::solution)
		sourceFolder = updateFolder(assignment_base + "_solution/", false);
	else
		sourceFolder = getFolder(assignment_base + '/', false);

	// tests folder
	if (opts::provided)
		testsFolder = updateFolder(assignment_base + "_provided/", false);
	else if (opts::newtests)
		testsFolder = updateFolder(assignment_base + "_newtests/", false);
	else
		testsFolder = updateFolder(assignment_base + "_tests/", false);
}


void monad::find_base_dir(const char * argv0)
{
	EXIT_IF_ERROR(argv0 == NULL);
	size_t argv0len = strlen(argv0);
	char * dir = new char[argv0len + 1];
	strncpy(dir, argv0, argv0len);
	dir[argv0len] = '\0';

	size_t i = argv0len + 1;
	do
	{
		i--;
		if (argv0[i] == '/') break;
	} while (i != 0);

	// Change directory
	if (i != 0)
	{
		dir[i] = '\0';
		EXIT_IF_ERROR(chdir(dir));
	}
	delete [] dir;

	// Ensure the dir is correct
	if (!exists("./.monadid"))
	{
		cerr << "Could not find monad directory. "
		        "Please run ./monad from the directory it is located in."
		     << endl;
		exit(-1);
	}
}


void monad::copyRequiredFiles()
{
	// Clear out the temp testing folder
	if (opts::clean)
		forceRemoveDir(gradeFolder);
	else
	{
		forceRemoveDir(tempFolder);
		EXIT_IF_ERROR(rename(gradeFolder.c_str(), tempFolder.c_str())); 
	}

	exec("/bin/mkdir",gradeFolder.c_str());

	// Copy and link appropriate files - parsed from config.ini
	importFiles(tempFolder, "./",         gradeFolder, config["Monad Files"]);
	importFiles(tempFolder, testsFolder,  gradeFolder, config["Testing Files"]);
	importFiles("",         sourceFolder, gradeFolder, config["Required Files"]);
	importFiles(tempFolder, "",           gradeFolder, config["Preserved Files"]);

	forceRemoveDir(tempFolder);

	getLibs(config["Libraries"]);
}


void monad::importFiles(const string & preservedFolder, const string & theSourceFolder,
                 const string & destFolder, const vector<string> & files)
{
	// 0 for student errors for missing Required Files dir
	int student_error_code = ((preservedFolder == "") ? 0 : -1);

	assertExists(destFolder);
	if (preservedFolder != "") assertExists(preservedFolder);
	if (theSourceFolder    != "") assertExists(theSourceFolder, student_error_code);

	for (size_t i = 0; i < files.size(); i++)
	{
		string preservedFile = preservedFolder + files[i];
		string destFile      = destFolder      + files[i];

		// Move the file from it's preservation instance
		if (preservedFolder != "" && exists(preservedFile) &&
		    (theSourceFolder == "" || (permissions(preservedFile) & S_IWUSR) == 0))
		{
//!!			cout << "mv " << preservedFile << ' ' << destFile << endl;
			EXIT_IF_ERROR(rename(preservedFile.c_str(), destFile.c_str()));
		}
		else if (theSourceFolder != "")
		{
			// copy the file from it's source
			string sourceFile = theSourceFolder + files[i];
			assertExists(sourceFile, student_error_code);

			// Remove hacky call to exec here...
			EXIT_IF_ERROR(exec("cp", "-RL", sourceFile.c_str(), destFile.c_str()) != 0,
				"cp " + sourceFile + " " + destFile + " failed");
		}
		else continue;

		// TODO (toole1) Protect files. This is hacky and should be in util
		// TODO (toole1) this should also be AFTER Pre-Make Commands
		// EXIT_IF_ERROR(chmod(destFile.c_str(),
		//	S_IRUSR | (permissions(destFile) & S_IXUSR)) != 0);
	}
}


void monad::getLibs(const vector<string> & libs)
{
	for (size_t lib_i = 0; lib_i < libs.size(); lib_i++)
	{
		string folder = updateFolder(libs[lib_i], false);
		protectDir(folder);
		chdir(gradeFolder.c_str());
		system(("/bin/ln -s ../"+folder+"* ./").c_str());
		chdir("..");
	}
}

string monad::updateFolder(const string & folder, bool link)
{
	string get = getFolder(folder, link);
	if (opts::update)
		exec(/*-1,*/ "svn","up", get.c_str());
	return get;
}

string monad::getFolder(const string & folder, bool link)
{
	// Look in the current folder
	string target = "./" + folder;
	if (exists(target + "/")) 
		return target + "/";

	// Look in the parent folder
	string source = "../" + folder;
	if (exists(source + "/"))
	{
		if (!link) return source + "/";
		EXIT_IF_ERROR(symlink(source.c_str(), target.c_str()) != 0);
		return target + "/";
	}

	// Maybe it actually *is* the parent folder
	string cwd   = getcwdstr();
	size_t cwd_i = findNthLast(cwd, '/', 2);
	if (cwd_i != string::npos &&
	    cwd.length() - cwd_i > folder.length() &&
	    cwd.compare(cwd_i, folder.length(), folder) == 0)
	{
		if (!link) return "../";
		EXIT_IF_ERROR(symlink("../", target.c_str()) != 0);
		return target + "/";
	}

	// Look two directories up and over - why not? If the parent folder is
	// the target source folder for the mp/lab, then the tests or libs
	// may be two up and over
	source = "../../" + folder;
	if (exists(source + "/"))
	{
		if (!link) return source + "/";
		EXIT_IF_ERROR(symlink(source.c_str(), target.c_str()) != 0);
		return target + "/";
	}

	// Check Subversion

	string svn_config_name;
	string svn_config_subdir;
	if (!opts::staff)
	{
		svn_config_name = "SVN Root";
		svn_config_subdir = "SVN Public Dir";
	}
	else
	{
		svn_config_name = "Staff SVN";
		svn_config_subdir = "Staff SVN Dir";
	}
	if (!config[svn_config_name].empty())
	{
		string svndir = config[svn_config_name][0] + "/" + config[svn_config_subdir][0] + "/" + folder;

		// TODO (toole1): Won't work if user needs to type password
		int svnstatus = exec(/*-1,*/ "svn","co",svndir.c_str());
		if (svnstatus == 0) return target + "/";
	}

	cerr << "Error: " << folder << " not found." << endl;
	exit(-1);
	return "";
}


// Execute a monad or command line command
void monad::exec_command(const string & command)
{
	vector<string> args = tokenize(command, ' ');

	// Allow processing of special internals
	if (args[0] == "rename_main")
	{
		EXIT_IF_ERROR(args.size() != 3, "rename_main must take 2 arguments: a file and a new name");
		rename_main(args[1], args[2]);
		return;
	}

#if DEBUG
	cout << "Pre-Make Command: " << command << endl;
#endif
	system(command.c_str());
}



