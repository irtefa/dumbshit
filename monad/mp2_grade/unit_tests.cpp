// CS 225 Lab02 Unit Tests

#include "easypng.h"
#include "util.h"
#include "proxy.h"

#include "image.h"

using namespace util;

#if MP_PART(1)

UNIT_TEST(test_invertcolors, 4, 1, 5000)
{
	Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();

	ASSERT(*myImage == PNG("soln_inverted.png"));
	delete myImage;
	PASS;
}

UNIT_TEST(test_flipleft, 3, 1, 5000)
{
	Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();
	myImage->flipleft();
	
	ASSERT(*myImage == PNG("soln_flipped.png"));
	delete myImage;
	PASS;
}

UNIT_TEST(test_adjustbrightness, 3, 1, 5000)
{
	Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();
	myImage->flipleft();
	myImage->adjustbrightness(20, 20, -40);

	ASSERT(*myImage == PNG("soln_brightened.png"));
	delete myImage;
	PASS;
}

#endif // MP_PART(1)

#if MP_PART(2)

#include "scene.h"

UNIT_TEST(test_drawscene, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	Image result = set->drawscene();
	ASSERT(result == PNG("soln_scene.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_changelayer, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);

	set->changelayer(1, 3);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene2.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_translate, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);

	set->translate(0, 50, 50);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene3.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_getpicture, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();

	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene4.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_deletepicture, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();
	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	
	set->deletepicture(3);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene5.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_cctor, 0, 1, 10000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();
	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	set->deletepicture(3);
	
	Scene* sc = new Scene(*set);
	sc->getpicture(0)->flipleft();
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene6.png")); // scene 5 and 6 should be the same
	result = sc->drawscene();
	ASSERT(result == PNG("soln_scene7.png"));
	delete set;
	delete sc;
	PASS;
}

UNIT_TEST(test_operator_equals, 0, 1, 10000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();
	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	set->deletepicture(3);
	Scene* sc = new Scene(*set);
	sc->getpicture(0)->flipleft();

	delete set;
	set = new Scene(5);
	*set = *sc;
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene8.png")); // scene 7 and 8 should be the same
	delete set;
	delete sc;
	PASS;
}

#endif
#include <iostream>
#include "monad_shared.h"
#include "util.h"

using namespace monad_shared;
using namespace util;
using std::cout;
using std::cerr;
using std::endl;

namespace monad_shared
{

namespace versioninfo
{
const char * official_name = "Monad Autograder";
const char * version_name  = "confession";
const Version version_num  = Version(2, 1, 2, 3);
const char * date          = "18 Jan 2012";
}

const char * unit_test_result::pass_string = "~~PASSED~~";
const size_t header_length = 64;

void printInfo()
{
	cout << endl
	     << versioninfo::official_name << endl
	     << "Version " << versioninfo::version_num << ": " << versioninfo::version_name << endl
		 << "Released " << versioninfo::date << endl
	     << "Developed by Jack Toole 2011-2012" << endl
	     << "Copyright 2011-2012 Jack Toole" << endl
	     << "Run monad --license to see licensing information" << endl
		 << endl;
}

namespace output
{

// Set EXIT_IF_ERROR message
void set_error_message()
{
	SET_ERROR_MESSAGE("Oops! Something went wrong inside of me.\n"
		"Please contact course staff with the following error details, and they'll figure it out:\n");
}

void header(const string & title)
{
	cout << title << "..." << endl
	     << string(header_length, '=') << endl;
}

void warning(const string & message)
{
	cerr << endl
	     << string(header_length, '*') << endl
		 << "WARNING!" << endl
		 << message << endl
	     << string(header_length, '*') << endl << endl;
}


void total_score(int32_t score, int32_t outof)
{
	if (outof < 0)
		output::header("Total score");
	else
		output::header("Total score (out of " + to_string(outof) + ")");
	
	cout << "TOTAL SCORE: " << score << endl << endl;
}

void testname(const unit_test_input & curr_test, int32_t max_testname_len, int32_t max_points_len)
{
	// Output test name
	int32_t pos = 0; // keep track of cursor position
	std::cout << curr_test.name() << ' ';
	pos += strlen(curr_test.name()) + 1;

	if (curr_test.is_valgrind())
	{
		cout << "(valgrind) ";
		pos += 11;
	}

	if (pos % 2 == max_testname_len % 2)
	{
		cout << ' ';
		pos++;
	}

	while (pos < max_testname_len + 1)
	{
		cout << ". ";
		pos += 2;
	}
	pos = 0; // reset column

	std::cout << "[" << curr_test.points() << " pts] ";
	pos += intlen(curr_test.points()) + 7;

	while (pos < max_points_len + 7)
	{
		cout << ' ';
		pos++;
	}

	cout << "- ";
}


void detailed_info(const unit_test_result & curr_test)
{
	std::cout << string(header_length, '-') << endl
			  << curr_test.name();
	if (curr_test.is_valgrind()) std::cout << " (run under valgrind)";
	std::cout << " [" << curr_test.points() << " points]" << endl;

	const string & error = curr_test.errormsg();
	const string & output = curr_test.output();

	if (curr_test.passed())
		std::cout << "Result: " << passed_string() << endl;
	else
		std::cout << "Result: " << failed_string() << ": " << error << endl;

	if (curr_test.time() < 0)
		cout << "Took unknown time (";
	else
		cout << "Took " << curr_test.time() << "ms (";
	cout << curr_test.timeout() << "ms timeout)" << endl;

	std::cout << "Output:" << endl
			  << string(header_length, '-') << endl;

	// Tab the output over to distinguish it from the test case
	if (output != "")
	{
		//std::cout << "    ";
		//replaceAllInternal(output,"\n","\n    ");
		std::cout << output;
		if (output[output.length() - 1] != '\n') std::cout << endl;
	}

	cout << endl;
}

string passed_string()
{
	return colorize::make_color(colorize::GREEN, "passed");
}

string failed_string()
{
	return colorize::make_color(colorize::RED  , "FAILED");
}

} // namespace output
} // namespace monad_shared

// proxy.cpp
// NOTE: This is a generic file. Actual unit tests are located in
//       unit_tests.cpp.
// By Jack Toole for CS 225 spring 2011

// For strsignal:
#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <algorithm>
#include <iomanip>
#include <numeric>

#include "memcheck.h"
#include "monad_shared.h"
#include "pipestream.h"
#include "proxy.h"
#include "util.h"
#include "valgrind.h"

using namespace std;
using namespace util;
using namespace monad_shared;


OUTPUT_CHECK(equals)
{
	return output == expected;
}


OUTPUT_CHECK(contains)
{
	return output.find(expected) != string::npos;
}


OUTPUT_CHECK(not_contains)
{
	return output.find(expected) == string::npos;
}


namespace proxy
{
	vector<unit_test_input> * global_tests = NULL;
	output_check_map * global_output_checks = NULL;

	double time_constant(size_t smaller, size_t larger) { return 1.0; }
	double time_logn    (size_t smaller, size_t larger) { return log(larger) / log(smaller); }
	double time_linear  (size_t smaller, size_t larger) { return (double)larger / smaller; }
	double time_nlogn   (size_t smaller, size_t larger) { return (larger*log(larger)) / (smaller*log(smaller)); }
	double time_nsquared(size_t smaller, size_t larger) { return ((double)larger*larger) / ((double)smaller*smaller); }
	double time_cubed   (size_t smaller, size_t larger) { return ((double)larger*larger*larger) / ((double)smaller*smaller*smaller); }
	double time_infinity(size_t smaller, size_t larger) { return std::numeric_limits<double>::max(); }

	runtime_ratio_func runtime_ratio[TIME_COUNT] =
	{
		time_constant,
		time_logn,
		time_linear,
		time_nlogn,
		time_nsquared,
		time_cubed,
		time_infinity
	};
	const char * runtime_str[TIME_COUNT] =
	{
		"O(1)",
		"O(logn)",
		"O(n)",
		"O(nlogn)",
//		"O(nrootn)",
		"O(n^2)",
		"O(n^3)",
		"O(infinity)"
	};
}



int main(int argc, char ** argv)
{
	using namespace proxy;
	
	// set up EXIT_IF_ERROR messages
	output::set_error_message();

	RunTimeEnvironment::Options opts;
	const char * testname = parse_options(argc, argv, opts);

	// Set up run-time environment
	RunTimeEnvironment env(global_tests, global_output_checks, opts, testname);

	// Set up the tests
	RunTests runner(env);

	// Execute
	return runner.execute();
}


namespace proxy {

// class add_unit_test
add_unit_test::add_unit_test(const char * name, unit_test_input::function func,
                             int32_t points_in_part, int32_t points_in_total, long timeout,
                             bool is_valgrind)
{
	lazy_init_global_tests();
	int32_t points = get_points(points_in_total, points_in_part);
	// Add to global tests vector
	global_tests->push_back(unit_test_input(name, func, points, timeout, is_valgrind));
}


// Check to make global tests vector
void add_unit_test::lazy_init_global_tests()
{
	if (global_tests == NULL)
		global_tests = new std::vector<unit_test_input>;
}

// Discriminate which points value to add
int32_t add_unit_test::get_points(int32_t points_in_total, int32_t points_in_part)
{
	#if MP_PART(NO_MP_PART)
		return points_in_total;
	#else
		return points_in_part;
	#endif
}


const char * parse_options(int argc, const char * const * const argv, RunTimeEnvironment::Options & opts)
{
	string getTestName = "all";

	OptionsParser parseopts;
	parseopts.addOption("verbose",  opts.verbose);
	parseopts.addOption("redirect", opts.redirect_test_output);
	parseopts.addOption("valgrind", opts.valgrind);
	parseopts.addArg(getTestName);
	parseopts.parse(argc, argv);

	const char * testname = "all";
	for (int32_t i = 0; i < argc; i++)
		if (getTestName == argv[i])
			testname = argv[i];
	return testname;
}


// class add_output_check
add_output_check::add_output_check(const char * name, output_check func)
{
	if (global_output_checks == NULL)
		global_output_checks = new output_check_map;
	(*global_output_checks)[name] = func;
}



// class Run_Time_Environment
RunTimeEnvironment::RunTimeEnvironment(vector<unit_test_input> *& init_tests,
                                       output_check_map *& init_output_checks,
                                       const Options & init_opts, const char * testname)
	: max_output_length(8*1024), //arbitrary
	  single_test_passed_string("Result: passed"),
	  heap_tests(init_tests),
	  output_checks(init_output_checks != NULL ? init_output_checks : new output_check_map),
	  opts(init_opts),
	  mode(strcasecmp(testname, "all") == 0 ? ALL_TESTS : SINGLE_TEST),
	  test_arg(testname)
{
	// Copy globals to the RunTimeEnvironment space
	// And remove them from the global scope
	static int8_t singleton = 0;
	EXIT_IF_ERROR(singleton++ != 0, "There may only be one runtime environment");
	EXIT_IF_ERROR(heap_tests == NULL, "No test cases found");
	
	init_tests = NULL;
	init_output_checks = NULL;
}


void RunTimeEnvironment::cleanup_globals()
{
	static bool called_already = false;
	if (!called_already)
	{
		if (heap_tests    != NULL) delete heap_tests;
		if (output_checks != NULL) delete output_checks;
		called_already = true;
	}
}



// class RunTests
RunTests::RunTests(RunTimeEnvironment & env)
	: environment(env)
{ }


int32_t RunTests::execute()
{
	int32_t return_code = execute_by_mode();
	environment.cleanup_globals();
	return return_code;
}


int32_t RunTests::execute_by_mode()
{
	if (environment.mode == SINGLE_TEST)
		return run_single_test(environment.test_arg);
	else if (environment.mode == ALL_TESTS)
		return run_all_tests();
	
	EXIT_IF_ERROR(true, string("Failed to implement case for mode ") + environment.mode);
	exit(-1);
}


int32_t RunTests::run_single_test(const char * testname)
{
	const vector<unit_test_input> & tests = *environment.heap_tests;

	for (size_t test_i = 0; test_i < tests.size(); test_i++)
		if (strcmp(tests[test_i].name(), testname) == 0)
			return run_single_test(tests[test_i]);

	cout << "Test not found" << endl;
	exit(-1);
}


int32_t RunTests::run_single_test(const unit_test_input & curr_test)
{
	cout << "Running " << curr_test.name() << " [worth "
		 << curr_test.points() << " points, output below]" << endl;

	unit_test_result result = execute_test(curr_test, false);

	const string & error  = result.errormsg();

	handle_single_test_output(result.output());

	if (result.passed())
		cout << environment.single_test_passed_string << endl;
	else
		cout << "Result: FAILED:" << endl << error << endl;

	return result.valgrind_flags();
}


void RunTests::handle_single_test_output(const string & output)
{
	if (output != "")
	{
		cout << output;
		if (output[output.size()-1] != '\n')
			cout << endl;
	}
}

int32_t foldTestScore (int score,  const unit_test_result & test) { return score  + test.points_scored(); }
int32_t foldTestPoints(int points, const unit_test_input  & test) { return points + test.points(); }

int RunTests::run_all_tests()
{
	const vector<unit_test_input> & tests = *environment.heap_tests;

	output::header("Running tests");

	int32_t points_sum = get_sum_points();
	int32_t max_testname_len = get_max_testname_length();
	int32_t max_points_len   = get_max_points_length();

#if 0 // removed due to partial compilation lowering this number artificially
	if (points_sum != 0 && points_sum < 100)
		output::warning("Unit test scores sum to " + to_string(points_sum) +
		                ", should be at least 100");
#endif
	if (points_sum > 125)
		output::warning("Unit test scores sum to " + to_string(points_sum) +
		                ", this will overflow the return value. Should be <= 125");

	vector<unit_test_result> results;
	for (size_t test_i = 0; test_i < tests.size(); test_i++)
	{
		output::testname(tests[test_i], max_testname_len, max_points_len);
		results.push_back(execute_test(tests[test_i], true));
		output_single_test_passfail(results.back());
	}

	const int32_t score = accumulate(results.begin(), results.end(), 0, foldTestScore);

	cout << endl << endl;
	output_detailed_info_if_any_failed(results, score);
	output::total_score(score, -1);
	
	return score;
}

int32_t RunTests::get_sum_points()
{
	static int32_t cached_sum = INT_MIN;
	if (cached_sum == INT_MIN)
		cached_sum = accumulate(environment.heap_tests->begin(), environment.heap_tests->end(), 0, foldTestPoints);
	return cached_sum;
}

int32_t RunTests::get_max_testname_length()
{
	const vector<unit_test_input> & tests = *environment.heap_tests;
	int32_t max_testname_len = 0;
	for (size_t test_i = 0; test_i < tests.size(); test_i++)
	{
		// TODO (toole1): This is horrible style!
		int32_t currlen = strlen(tests[test_i].name()) + (int)tests[test_i].is_valgrind() * 11; // strlen(" (valgrind)");

		if (currlen > max_testname_len)
			max_testname_len = currlen;
	}
	return max_testname_len;
}

int32_t RunTests::get_max_points_length()
{
	const vector<unit_test_input> & tests = *environment.heap_tests;
	uint32_t max_points_len = 0;
	for (size_t test_i = 0; test_i < tests.size(); test_i++)
		max_points_len = max(max_points_len, intlen(tests[test_i].points()));
	return max_points_len;
}

void RunTests::output_detailed_info_if_any_failed(const vector<unit_test_result> & results, int32_t score)
{
	if (count_if(results.begin(), results.end(), unit_test_result::_failed) ||
			environment.opts.verbose)
		output_detailed_tests_info(results, score);
}
	
	
void RunTests::output_detailed_tests_info(const vector<unit_test_result> & results, int32_t score)
{
	output::total_score(score, -1);
	cout << endl << endl;
	
	output::header("Detailed test output");
	
	for (size_t test_i = 0; test_i < results.size(); test_i++)
		if (results[test_i].failed() || environment.opts.verbose)
			output::detailed_info(results[test_i]);
	
	cout << endl << string(64, '-') << endl; // TODO (toole1): poor style, should be refactored to monad_shared::output
}


void RunTests::output_single_test_passfail(const unit_test_result & curr_test)
{
	if (curr_test.passed())
		std::cout << output::passed_string() << endl;
	else
		std::cout << output::failed_string() << ": " << curr_test.errormsg() << endl;
}

test_execution::test_execution(const unit_test_input & _test, RunTimeEnvironment & env, bool enable_valgrind_call)
	: test(_test), environment(env)
{
	do_valgrind = enable_valgrind_call && (test.is_valgrind() || env.opts.valgrind);
//!!	if (!do_valgrind)
//!!		test.checkstream = new pipestream; // TODO (reimplement)
}

void test_execution::child()
{
	fmsg_pipe.close_read();
	cout_pipe.close_read();
	nums_pipe.close_read();

	// Redirect stdout/stderr to pipe
	if (environment.opts.redirect_test_output)
	{
		cout_pipe.steal_output(STDOUT_FILENO);
		cout_pipe.steal_output(STDERR_FILENO);
	}

	if (do_valgrind)
	{
		child_valgrind();
	}
	else // if (!test.is_valgrind)
	{
		child_test();
	}
}

void test_execution::parent()
{
	fmsg_pipe.close_write();
	cout_pipe.close_write();
	nums_pipe.close_write();
//!!	if (test.checkstream != NULL)
	checkstream.close_write();

	// Read stdout/stderr pipe while process is running
	if (environment.opts.redirect_test_output)
		cout_pipe >> setmax(environment.max_output_length) >> output;
	else
		output = "Test output was displayed above instead of being buffered\n";
	
	cout_pipe.close_read();
}

unit_test_result test_execution::result(int8_t return_code)
{
	if (do_valgrind)
		return after_valgrind_success(return_code);
	else
		return after_test_success();
}

unit_test_result test_execution::result(const Signal & s)
{
	string errormsg;
	long time;
	int32_t valgrind_flags = get_valgrind_flags(true);

	fmsg_pipe.close();
	nums_pipe.close();
	if (environment.is_timeout_signal(s))
	{
		errormsg = string("Timed out") + " (" + to_string(test.timeout()) + "ms)";
		time = test.timeout();
	}
	else
		errormsg = s.what();
	
	return unit_test_result(test, errormsg, output, time, valgrind_flags);
}


unit_test_result RunTests::execute_test(const unit_test_input & test, bool enable_valgrind_call)
{
	cout << std::flush;
	test_execution executor(test, environment, enable_valgrind_call);
	try
	{
		int32_t return_code = fork_execute(executor);
		return executor.result(return_code);
	}
	catch (Signal & s)
	{
		return executor.result(s);
	}
}

template <typename F>
int32_t fork_execute(F & executor)
{
	// Fork
	pid_t process_id;
	process_id = fork();
	EXIT_IF_ERROR(process_id < 0, "Could not fork application");

	if (process_id == 0)
	{
		executor.child();
		exit(0);
	}
	else // if (process_id > 0)
	{
		executor.parent();

		int child_status;
		pid_t ws = waitpid(process_id, &child_status, 0); //should return immediately because it's after parent()
		EXIT_IF_ERROR(ws == -1);

		if (WIFEXITED(child_status))
			return WEXITSTATUS(child_status);
		else if (WIFSIGNALED(child_status))
			throw Signal(WTERMSIG(child_status));
		else
			throw Signal(SIGSTOP);
	}
}

void test_execution::child_valgrind()
{
	// We're giving up control to valgrind, so we can't
	// Use anything but the cout pipe now
	fmsg_pipe.close_write();
	nums_pipe.close_write();
	
	start_timeout();
	exec("valgrind", "--dsymutil=yes", "--trace-children=yes", /*"--log-fd=-1",*/ "-q", "./proxy", test.name(), NULL);
}


void test_execution::child_test()
{
	checkstream.close_read();
	// Execute test
	bool test_failed = false;
	long test_time = -1;
	start_timeout();
	try
	{
		test.execute(checkstream); // execute function
		test_time = end_timeout();
		fmsg_pipe << unit_test_result::pass_string;
	}
	catch (Failure & failure)
	{
		test_time = end_timeout();
		test_failed = true;
		// Write failure message to pipe
		fmsg_pipe << failure.message();
	}
	fmsg_pipe.close();

	// write time and valgrind flags to pipe
//!!	delete test.checkstream;
	checkstream.close();
	environment.cleanup_globals();
	int32_t valgrind_flags = get_valgrind_flags(test_failed);
	nums_pipe << test_time;
	nums_pipe << valgrind_flags;
	nums_pipe.close();
}


unit_test_result test_execution::after_valgrind_success(int8_t return_code)
{
	fmsg_pipe.close_read();
	nums_pipe.close_read();

	string errormsg;

	size_t last_endl = findNthLast(output, '\n', 2);
	int32_t valgrind_flags = return_code;

	if (last_endl == string::npos)
	{
		if (environment.opts.redirect_test_output)
			errormsg = "Valgrind test did not complete";
		else
			errormsg = "Valgrind test output was not redirected to pipe because --redirect was set.";
	}
	else
	{
		errormsg = output.substr(last_endl + 1,
				output.length() - last_endl - 2);

		if (errormsg == environment.single_test_passed_string)
			errormsg = get_valgrind_string(valgrind_flags);
			// This will always be unit_test::pass_string unless someone tried to hack monad, in which case
			// basing our passing on the return code (valgrind flags) rather than string parsing is the
			// right thing to do
	}

	return unit_test_result(test, errormsg, output, -1, valgrind_flags);
}


unit_test_result test_execution::after_test_success()
{
	string errormsg;
	long time;
	int32_t valgrind_flags;

	fmsg_pipe >> errormsg;
	fmsg_pipe.close();
	nums_pipe >> time;
	nums_pipe >> valgrind_flags;
	nums_pipe.close();
	
	// Check for output's correctness, if that was a condition of passing
	if (errormsg == unit_test_result::pass_string)
	{
		while (!checkstream.eof())
		{
			string checkname;
			string checkstr;
			checkstream >> checkname;
			if (checkstream.eof()) break;
			checkstream >> checkstr;
			if (checkstream.eof()) break;

			output_check check_function = (*environment.output_checks).find(checkname)->second;
			if (check_function == NULL)
			{
				cerr << "Internal Error: in test " << test.name() << ": "
				     << checkname << " is not a registered OUTPUT_CHECK function" << endl;
				exit(-2);
			}

			if (!check_function(output, checkstr))
				errormsg = "Incorrect Terminal Output";
		}
	}
	
	if (errormsg == unit_test_result::pass_string)
		errormsg = get_valgrind_string(valgrind_flags);

//!!	delete test.checkstream;
	checkstream.close();
	
	return unit_test_result(test, errormsg, output, time, valgrind_flags);
}


int32_t get_valgrind_flags(bool test_failed)
{
	// Check for valgrind errors or leaks (if running under valgrind)
	unsigned long errors     = 0;
	unsigned long leaked     = 0;
	unsigned long dubious    = 0;
	unsigned long reachable  = 0;
	unsigned long suppressed = 0;

	errors = VALGRIND_COUNT_ERRORS;
	VALGRIND_DO_LEAK_CHECK; //QUICK
	VALGRIND_COUNT_LEAK_BLOCKS(leaked, dubious, reachable, suppressed);

	return bitflags(test_failed, errors, leaked, dubious, reachable);
}


const char * get_valgrind_string(int32_t flags)
{
	if (flags == 0) return unit_test_result::pass_string;

	bool test_failed = bitflag(flags, 0);
	bool errors      = bitflag(flags, 1);
	bool leaked      = bitflag(flags, 2);
	bool dubious     = bitflag(flags, 3);
	bool reachable   = bitflag(flags, 4);

	if (test_failed) return "Test failed (see output)";
	if (errors)      return "Invalid read/write errors";
	if (leaked)      return "Directly lost memory leaks";
	if (dubious)     return "Possibly lost memory leaks";
	// For now we will ignore reachable errors, as they are always present on Mac
	// TODO (toole1): Refactor. Still reachable should still hit "unknown" below, not be a free pass
	// (this doesn't impact current code paths, but is inelegant)
	if (reachable)   return unit_test_result::pass_string; //"Still-reachable memory leaks";
	return "Unknown memory errors";
}

bool test_execution::prof_timeout_enabled()
{
	struct itimerval temp;
	errno = 0;
	if (getitimer(ITIMER_PROF, &temp) == 0)
		return true;
	if (errno == EINVAL)
		return false;
	cerr << __FILE__ << ":" << __LINE__ << ": ERROR: getitimer failed" << endl;
	exit(-1);
}

void test_execution::start_timeout()
{
	static const bool prof_enabled = prof_timeout_enabled();

	struct itimerval timeout;
	timeout.it_interval.tv_sec  = 0;
	timeout.it_interval.tv_usec = 0;
	timeout.it_value.tv_sec  = test.timeout()/1000;
	timeout.it_value.tv_usec = (test.timeout()%1000) * 1000;

	if (prof_enabled)
	{
		EXIT_IF_ERROR(setitimer(ITIMER_PROF, &timeout, NULL));
		// second real time signal in case the student calls a blocking call
		timeout.it_value.tv_sec *= 10;
		EXIT_IF_ERROR(setitimer(ITIMER_REAL, &timeout, NULL));
	}
	else
	{
		EXIT_IF_ERROR(setitimer(ITIMER_REAL, &timeout, NULL));
	}
}


long test_execution::end_timeout()
{
	static const bool prof_enabled = prof_timeout_enabled();

	struct itimerval timeout;
	timeout.it_interval.tv_sec  = 0;
	timeout.it_interval.tv_usec = 0;
	timeout.it_value.tv_sec  = 0;
	timeout.it_value.tv_usec = 0;
	struct itimerval remaining;

	if (prof_enabled)
	{
		EXIT_IF_ERROR(setitimer(ITIMER_PROF, &timeout, &remaining));
		EXIT_IF_ERROR(setitimer(ITIMER_REAL, &timeout, NULL));
	}
	else
	{
		EXIT_IF_ERROR(setitimer(ITIMER_REAL, &timeout, &remaining));
	}

	// There seems to be a strange -1 error here. I may just be tired,
	// but I can't figure out why right now
	long time = test.timeout() - remaining.it_value.tv_sec*1000 - remaining.it_value.tv_usec/1000;
	return (time < 0) ? 0 : time;
}



} // namespace proxy

// CS 225 util.h
// Created Spring 2011 by Jack Toole

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include "util.h"

extern char ** environ; // man 7 environ

namespace util
{

namespace internal
{
const char * error_prefix = "";

template<typename StrType>
void exit_if_error_output(const char * file, int32_t line, StrType message)
{
	if (util::internal::error_prefix != NULL)
		cerr << util::internal::error_prefix;
	cerr << file << ":" << line << ": " << message;
	if (errno != 0)
		cerr << ": " << strerror(errno);
	cerr << endl;
	exit(-1);
}

}

void SET_ERROR_MESSAGE(const char * message)
{
	internal::error_prefix = message;
}

namespace internal
{
namespace exec
{

char * allocateCstr(const string & str)
{
	char * cstr = new char[str.size() + 1];
	str.copy(cstr, str.size());
	cstr[str.size()] = '\0';
	return cstr;
}

pair<int, int> getFdsFromStream(const ostream * stream)
{
	int redirect_fd;
	int outpipe_fd = -1;

	if (stream == NULL)
		redirect_fd = -1;
	else if (stream == &cout || stream == &cerr) // we don't handle cerr right now; it is just left unpiped
		redirect_fd = STDOUT_FILENO;
	else
	{
		int pipe_fds[2];
		EXIT_IF_ERROR(pipe(pipe_fds) != 0);
		redirect_fd = pipe_fds[1];
		outpipe_fd = pipe_fds[0];
	}

	return make_pair(redirect_fd, outpipe_fd);
}

struct exec_timers
{
	struct itimerval remaining_real;
	struct itimerval remaining_virtual;
	struct itimerval remaining_prof;
	bool supports_virtual;
	bool supports_prof;
	exec_timers() : supports_virtual(true), supports_prof(true) { }
};

exec_timers get_exec_timers()
{
	exec_timers result;
	
	EXIT_IF_ERROR(getitimer(ITIMER_REAL, &result.remaining_real));
	
	if (getitimer(ITIMER_VIRTUAL, &result.remaining_virtual) != 0)
	{
		if (errno == EINVAL)
		{
			result.supports_virtual = false;
			errno = 0;
		}
		else
			exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_VIRTUAL) failed");
	}
	
	if (getitimer(ITIMER_PROF, &result.remaining_prof) != 0)
	{
		if (errno == EINVAL)
		{
			result.supports_prof = false;
			errno = 0;
		}
		else
			exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_PROF) failed");
	}

	return result;
}

void set_exec_timers(const exec_timers & timers)
{
	EXIT_IF_ERROR(setitimer(ITIMER_REAL, &timers.remaining_real, NULL));
	if (timers.supports_virtual) EXIT_IF_ERROR(setitimer(ITIMER_VIRTUAL, &timers.remaining_virtual, NULL));
	if (timers.supports_prof)    EXIT_IF_ERROR(setitimer(ITIMER_PROF,    &timers.remaining_prof, NULL));
}

void redirect_to_fd(const int redirect_fd)
{
	if (redirect_fd == -1)
	{
		int devnull_fd = open("/dev/null", O_WRONLY | O_NONBLOCK);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		dup2(devnull_fd, STDOUT_FILENO);
		dup2(devnull_fd, STDERR_FILENO);
		close(devnull_fd);
	}
	else if (redirect_fd != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		dup2(redirect_fd, STDOUT_FILENO);
		dup2(redirect_fd, STDERR_FILENO);
		close(redirect_fd);
	}
}

char ** cstr_array_from_vector_string(const string & command, const vector<string> & args)
{
	// TODO (toole1): check this doesn't cause a memleak
	char ** args_cstr = new char*[args.size() + 2];
	args_cstr[0] = allocateCstr(command);
	for (size_t i = 0; i < args.size(); i++)
		args_cstr[i + 1] = allocateCstr(args[i]);
	args_cstr[args.size() + 1] = NULL;
	return args_cstr;
}

} // namespace exec
} // namespace internal

// heavily refactored, but originally from:
// http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
int8_t exec(const string & command, const vector<string> & args, ostream * output)
{
	using namespace internal;
	using namespace internal::exec;

	pair<int, int> fds = getFdsFromStream(output);
	int redirect_fd = fds.first;
	int outpipe_fd  = fds.second;

	exec_timers timers = get_exec_timers();
	
	pid_t pid = fork();
	EXIT_IF_ERROR(pid < 0);
	if (pid == 0)
	{
		set_exec_timers(timers);
		redirect_to_fd(redirect_fd);
		if (outpipe_fd != -1)
			close(outpipe_fd);

		// Sanitize environment
		char path[] = "PATH=/bin/:/usr/bin:/usr/local/bin";
		// Turn off glibc errors default write-to-terminal behaviour, because
		// it does not get caught by stderr. This instead results in an abort.
		char redirect_glibc[] = "LIBC_FATAL_STDERR_=1";
		char * newenv[] = { path, redirect_glibc, NULL };
		environ = newenv;

		char ** args_cstr = cstr_array_from_vector_string(command, args);

		// Swap out child process image with the command, searching
		// in the specified path
		execvp(command.c_str(), args_cstr);
		
        // An error occured
		cerr << "exec(" << '\"' << command << '\"';
		for (size_t i = 0; i < args.size(); i++)
			cerr << ", \"" << args[i] << "\"";
		cerr << ") failed: " << strerror(errno) << endl;
		exit(-1);
	}
	else
	{
		// Take the output of the pipe and put it into the *output stream
		if (outpipe_fd != -1)
		{
			EXIT_IF_ERROR(output == NULL);
			close(redirect_fd);

			vector<char> buffer(1024);
			ssize_t char_read_count;
			do
			{
				errno = 0;
				char_read_count = ::read(outpipe_fd, &buffer[0], buffer.size() - 1);
				
				if (char_read_count < 0 && errno == EINTR) continue;
				EXIT_IF_ERROR(char_read_count < 0);
				EXIT_IF_ERROR(static_cast<size_t>(char_read_count) + 1 > buffer.size());
				
				buffer[char_read_count] = '\0';
				*output << &buffer[0];

			} while (char_read_count > 0);
		}

		int childExitStatus;
		/* parent - wait for child - this has all error handling, you
		 * could just call wait() as long as you are only expecting to
		 * have one child process at a time.
		 */
		pid_t ws = waitpid( pid, &childExitStatus, 0);
		EXIT_IF_ERROR(ws == -1);

		if (WIFEXITED(childExitStatus)) /* exit code in childExitStatus */
		{
			int8_t status = WEXITSTATUS(childExitStatus); /* zero is normal exit */
			/* handle non-zero as you wish */
			return status;
		}
		else if (WIFSIGNALED(childExitStatus)) /* killed */
		{
			// No idea why I'm doing this anymore... if it segfaults, you do too??
			kill(getpid(), WTERMSIG(childExitStatus));
			return -1;
		}
		else if (WIFSTOPPED(childExitStatus)) /* stopped */
		{
			//cout << "exec error: " << __LINE__ << endl;
			return -1;
		}
		else
			EXIT_IF_ERROR(true);
		exit(-1);
	}
}

// TODO (toole1) this is a total hack, should use execvp like exec() below
// originally from:
// http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
int8_t exec(int redirect_fd, const string & command, const vector<string> & args)
{
	using namespace internal::exec;

	// For debugging:
#if 0
	cerr << "exec(" << '\"' << command << '\"';
	for (size_t i = 0; i < args.size(); i++)
		cerr << ", \"" << args[i] << "\"";
	cerr << ")" << endl;
#endif

	// avoid self destruction errors from closing then trying to duplicate output
	// you can't redirect to what's already there
	if (redirect_fd == STDOUT_FILENO || redirect_fd == STDERR_FILENO)
		redirect_fd = STDOUT_FILENO;

	// Save timer values :)
	// These are preserved across the parent, but not inherited by the child
	// let's change that
	struct itimerval remaining_real;
	struct itimerval remaining_virtual;
	struct itimerval remaining_prof;
	bool supports_virtual = true;
	bool supports_prof    = true;
	EXIT_IF_ERROR(getitimer(ITIMER_REAL,    &remaining_real));
	if (getitimer(ITIMER_VIRTUAL, &remaining_virtual) != 0)
	{
		if (errno == EINVAL)
		{
			supports_virtual = false;
			errno = 0;
		}
		else
			internal::exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_VIRTUAL) failed");
	}
	if (getitimer(ITIMER_PROF, &remaining_prof) != 0)
	{
		if (errno == EINVAL)
		{
			supports_prof = false;
			errno = 0;
		}
		else
			internal::exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_PROF) failed");
	}

	pid_t pid = fork();

	if (pid == 0) /* child */
	{

		// Restore timers
		EXIT_IF_ERROR(setitimer(ITIMER_REAL, &remaining_real, NULL));
		if (supports_virtual) EXIT_IF_ERROR(setitimer(ITIMER_VIRTUAL, &remaining_virtual, NULL));
		if (supports_prof)    EXIT_IF_ERROR(setitimer(ITIMER_PROF,    &remaining_prof, NULL));

		if (redirect_fd == -1)
		{
			int devnull_fd = open("/dev/null", O_WRONLY | O_NONBLOCK);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			dup2(devnull_fd, STDOUT_FILENO);
			dup2(devnull_fd, STDERR_FILENO);
			close(devnull_fd);
		}
		else if (redirect_fd != STDOUT_FILENO)
		{
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			dup2(redirect_fd, STDOUT_FILENO);
			dup2(redirect_fd, STDERR_FILENO);
		}

		// Sanitize the environment
#if 1 //!! hack!
		char path[] = "PATH=/bin/:/usr/bin:/usr/local/bin";
		// Turn off glibc errors default write-to-terminal behaviour, because
		// it does not get caught by stderr. This instead results in an abort.
		char redirect_glibc[] = "LIBC_FATAL_STDERR_=1";
		char * newenv[] = { path, redirect_glibc, NULL };
		//char * newenv[] = { path, NULL };
		environ = newenv;
#endif

		// TODO (toole1): check this doesn't cause a memleak
		char ** args_cstr = new char*[args.size() + 2];
		args_cstr[0] = allocateCstr(command);
		for (size_t i = 0; i < args.size(); i++)
			args_cstr[i + 1] = allocateCstr(args[i]);
		args_cstr[args.size() + 1] = NULL;
		
		// Swap out child process image with the command, searching
		// in the specified path
		execvp(command.c_str(), args_cstr);
		
        // An error occured
		cerr << "exec(" << '\"' << command << '\"';
		for (size_t i = 0; i < args.size(); i++)
			cerr << ", \"" << args[i] << "\"";
		cerr << ") failed: " << strerror(errno) << endl;
		exit(-1);
	}
	else if (pid < 0)
	{
		/* error - couldn't start process - you decide how to handle */
		return -1;
	}
	else
	{
		int childExitStatus;
		/* parent - wait for child - this has all error handling, you
		 * could just call wait() as long as you are only expecting to
		 * have one child process at a time.
		 */
		pid_t ws = waitpid( pid, &childExitStatus, 0);
		if (ws == -1)
		{ /* error - handle as you wish */
			//cout << "exec error: " << __LINE__ << endl;
			return -1;
		}

		if (WIFEXITED(childExitStatus)) /* exit code in childExitStatus */
		{
			int8_t status = WEXITSTATUS(childExitStatus); /* zero is normal exit */
			/* handle non-zero as you wish */
			return status;
		}
		else if (WIFSIGNALED(childExitStatus)) /* killed */
		{
			kill(getpid(), WTERMSIG(childExitStatus));
			return -1;
		}
		else if (WIFSTOPPED(childExitStatus)) /* stopped */
		{
			//cout << "exec error: " << __LINE__ << endl;
			return -1;
		}
		else
			return -1;
	}
}


// originally from stackoverflow.com user plinth
// http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
// Modified by Jack Toole
int8_t exec(int redirect_fd, const char * command,
            const char * arg1,
            const char * arg2,
            const char * arg3,
            const char * arg4,
            const char * arg5,
            const char * arg6)
{
	int childExitStatus;
	pid_t pid;

	const char * args[] = {arg1, arg2, arg3, arg4, arg5, arg6};
	const size_t args_count = (sizeof args) / (sizeof args[0]);

	// shift all nulls to end
	size_t first_null = 0;
	for (size_t i = 0; i < args_count; i++)
		if (args[i] != NULL)
			swap(args[i], args[first_null++]);

	// For debugging:
#if 0
	cerr << "exec(" << '\"' << command << '\"';
	for (size_t i = 0; i < args_count; i++)
		if (args[i] != NULL) cerr << ", \"" << args[i] << "\"";
	cerr << ")" << endl;
#endif

	// avoid self destruction errors from closing then trying to duplicate output
	// you can't redirect to what's already there
	if (redirect_fd == STDOUT_FILENO || redirect_fd == STDERR_FILENO)
		redirect_fd = STDOUT_FILENO;

	// Save timer values :)
	// These are preserved across the parent, but not inherited by the child
	// let's change that
	struct itimerval remaining_real;
	struct itimerval remaining_virtual;
	struct itimerval remaining_prof;
	bool supports_virtual = true;
	bool supports_prof    = true;
	EXIT_IF_ERROR(getitimer(ITIMER_REAL,    &remaining_real));
	if (getitimer(ITIMER_VIRTUAL, &remaining_virtual) != 0)
	{
		if (errno == EINVAL)
		{
			supports_virtual = false;
			errno = 0;
		}
		else
			internal::exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_VIRTUAL) failed");
	}
	if (getitimer(ITIMER_PROF, &remaining_prof) != 0)
	{
		if (errno == EINVAL)
		{
			supports_prof = false;
			errno = 0;
		}
		else
			internal::exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_PROF) failed");
	}

	pid = fork();

	if (pid == 0) /* child */
	{

		// Restore timers
		EXIT_IF_ERROR(setitimer(ITIMER_REAL, &remaining_real, NULL));
		if (supports_virtual) EXIT_IF_ERROR(setitimer(ITIMER_VIRTUAL, &remaining_virtual, NULL));
		if (supports_prof)    EXIT_IF_ERROR(setitimer(ITIMER_PROF,    &remaining_prof, NULL));

		if (redirect_fd == -1)
		{
			int devnull_fd = open("/dev/null", O_WRONLY | O_NONBLOCK);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			dup2(devnull_fd, STDOUT_FILENO);
			dup2(devnull_fd, STDERR_FILENO);
			close(devnull_fd);
		}
		else if (redirect_fd != STDOUT_FILENO)
		{
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			dup2(redirect_fd, STDOUT_FILENO);
			dup2(redirect_fd, STDERR_FILENO);
		}

		// Sanitize the environment
#if 1 //!! hack!
		char path[] = "PATH=/bin/:/usr/bin:/usr/local/bin";
		// Turn off glibc errors default write-to-terminal behaviour, because
		// it does not get caught by stderr. This instead results in an abort.
		char redirect_glibc[] = "LIBC_FATAL_STDERR_=1";
		char * newenv[] = { path, redirect_glibc, NULL };
		//char * newenv[] = { path, NULL };
		environ = newenv;
#endif

		// Swap out child process image with the command, searching
		// in the specified path
		execlp(command, command, args[0], args[1], args[2], args[3], args[4], args[5], NULL);
		
        // An error occured
		cerr << "exec(" << '\"' << command << '\"';
		for (size_t i = 0; i < args_count; i++)
			if (args[i] != NULL) cerr << ", \"" << args[i] << "\"";
		cerr << ") failed: " << strerror(errno) << endl;
		exit(-1);
	}
	else if (pid < 0)
	{
		/* error - couldn't start process - you decide how to handle */
		return -1;
	}
	else
	{
		/* parent - wait for child - this has all error handling, you
		 * could just call wait() as long as you are only expecting to
		 * have one child process at a time.
		 */
		pid_t ws = waitpid( pid, &childExitStatus, 0);
		if (ws == -1)
		{ /* error - handle as you wish */
			//cout << "exec error: " << __LINE__ << endl;
			return -1;
		}

		if (WIFEXITED(childExitStatus)) /* exit code in childExitStatus */
		{
			int8_t status = WEXITSTATUS(childExitStatus); /* zero is normal exit */
			/* handle non-zero as you wish */
			return status;
		}
		else if (WIFSIGNALED(childExitStatus)) /* killed */
		{
			kill(getpid(), WTERMSIG(childExitStatus));
			return -1;
		}
		else if (WIFSTOPPED(childExitStatus)) /* stopped */
		{
			//cout << "exec error: " << __LINE__ << endl;
			return -1;
		}
		else
			return -1;
	}
}

const char * Signal::what() const
{
	const char * desc = strsignal(signum);
	return (desc == NULL) ? "Unknown Signal" : desc;
}


int chdir(const string & dir)
{
	return ::chdir(dir.c_str());
}

string stripTrailingSlash(const string & path)
{
	if (path[path.length() - 1] == '/')
		return path.substr(0, path.length() - 1);
	else
		return path;
}

string getBaseDir(const string & path)
{
	EXIT_IF_ERROR(path.length() == 0);
	if (path[path.length() - 1] == '/') return path;
	if (exists(path + "/")) return path + "/";
	size_t slash_pos = path.find_last_of('/');
	if (slash_pos == string::npos) return "./";
	return path.substr(0, slash_pos);
}

void assertExists(const string & path, int exit_code /* = -1 */)
{
	if (!exists(path))
	{
		cerr << "Error: " << path << " does not exist." << endl;
		exit(exit_code);
	}
}

bool exists(const string & path)
{
	// Try stat-ing it
	struct stat st;
	if (stat(path.c_str(), &st) != 0) return false;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return false;

	// Check for correct file/directory nature
	if (path[path.length()-1] != '/') return S_ISREG(st.st_mode);

	// Otherwise we want a directory
	if ((st.st_mode & S_IXUSR) == 0) return false;
	return S_ISDIR(st.st_mode);
}


mode_t permissions(const string & path)
{
	// Try stat-ing it
	struct stat st;
	if (stat(path.c_str(), &st) != 0) return -1;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return -1;

	return (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}


void forceRemoveDir(string dir)
{
	size_t len = dir.length();
	if (dir[len-1] == '/') dir[len-1] = '\0';
	EXIT_IF_ERROR(exec("rm","-rf",dir.c_str()) != 0);
	if (dir[len-1] == '\0') dir[len-1] = '/';
}


string getcwdstr()
{
	int len = 256;
	char * buffer = new char[len];

	char * ret = getcwd(&buffer[0], len - 1);
	while (ret == NULL && errno == ERANGE)
	{
		len *= 2;

		delete buffer;
		buffer = new char[len];

		ret = getcwd(&buffer[0], len - 1);
	}

	EXIT_IF_ERROR(ret == NULL);

	string cwdstr(buffer);
	delete buffer;

	return cwdstr + "/";
}


void copyFile(const string & source, const string & dest)
{
	assertExists(source);
	vector<string> folders = tokenize(dest, '/');
	string currdir = "";
	for (size_t i = 0; i < folders.size() - 1; i++)
	{
		currdir += folders[i] + '/';
		if (!exists(currdir))
			exec("mkdir", currdir.c_str());
	}
	exec("cp", source.c_str(), dest.c_str());
}

void copyFiles(const string & sourceFolder, const string & destFolder, const vector<string> & files)
{
	assertExists(destFolder);
	for (size_t i = 0; i < files.size(); i++)
	{
		string sourceFile = sourceFolder + files[i];
		assertExists(sourceFile);
		copyFile(sourceFile, destFolder);
	}
}


void protectFiles(const string & folder, const vector<string> & files)
{
#if 0 // (debug)
	for (size_t i = 0; i < files.size(); i++)
	{
		string file = folder + files[i];
		assertExists(file);

		if (chmod(file.c_str(), S_IRUSR) != 0)
		{
			perror("chmod failed");
			exit(-1);
		}
	}
#endif
}

void protectDir(const string & dir)
{
	// (debug) EXIT_IF_ERROR(exec("/bin/chmod", "-R", "ugoa-w", dir.c_str()) != 0);
}

// Originally from Simon Biber
// http://bytes.com/topic/c/answers/545614-list-files-current-directory
vector<string> get_files_in_dir(const string & dir, bool concatdir /* = true */)
{
	EXIT_IF_ERROR(dir == "" || dir[dir.length()-1] != '/', "Directory name must end in a '/'");
	
	vector<string> files;
	DIR * dirp = opendir(dir.c_str());
	if (dirp == NULL) return files;
	
	struct dirent * ent = readdir(dirp);
	while (ent != NULL)
	{
		string file = ent->d_name;
		if (file != "." && file != "..")
			files.push_back(concatdir ? dir + file : file);
		ent = readdir(dirp);
	}

	closedir(dirp);
	return files;
}

bool is_symlink(const string & file)
{
	// Try lstat-ing it
	struct stat st;
	if (lstat(file.c_str(), &st) != 0) return -1;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return false;

	// & with symlink bit
	return (S_ISLNK(st.st_mode)) != 0;
}

string get_symlink_target(const string & symlink)
{
	const size_t buf_size = 4096;
	char buf[buf_size+1]; // TODO (toole1): hack-y value
	ssize_t len = readlink(symlink.c_str(), buf, buf_size);
	EXIT_IF_ERROR(len < 0 || static_cast<size_t>(len) == buf_size, "Error getting target of symlink " + symlink);
	buf[len] = '\0';
	return string(buf);
}

void linkDirs(const string & sourceFolder, const string & destFolder, const vector<string> & dirs)
{
	assertExists(destFolder);
	for (size_t i = 0; i < dirs.size(); i++)
	{
		string source = sourceFolder + dirs[i];
		string target = destFolder   + dirs[i];

		// Check for redundant monad/ directory
		// This allows the monad/ dir to be safely renamed
		if (replaceFirst(source, "/../monad/","/"))
			replaceFirst(target, "/monad/","/");

		assertExists(destFolder + source + '/');

		if (symlink(source.c_str(), target.c_str()) != 0)
		{
			cerr << "symlink failed: " << target << ": ";
			perror(NULL);
			exit(-1);
		}
	}
}


bool replaceFirst(string & str, const string & toreplace, const string & with)
{
	size_t i = str.find(toreplace);
	if (i != string::npos)
	{
		str.replace(i,toreplace.length(),with);
		return true;
	}
	return false;
}

size_t replaceAll(string & str, const string & toreplace, const string & with)
{
	size_t i = str.find(toreplace);
	size_t count = 0;

	while (i != string::npos)
	{
		str.replace(i,toreplace.length(),with);
		i = str.find(toreplace, i + with.length());
		count++;
	}

	return count;
}

size_t replaceAllInternal(string & str, const string & toreplace, const string & with)
{
	size_t i = str.find(toreplace);
	size_t count = 0;

	while ((i != string::npos) && (i != str.length() - toreplace.length()))
	{
		str.replace(i,toreplace.length(),with);
		i = str.find(toreplace, i + with.length());
		count++;
	}

	return count;
}


size_t findNthLast(const string & str, char c, size_t n)
{
	if (str.length() == 0) return string::npos;
	size_t i = str.length() - 1;

	do
	{
		if (str[i] == c) n--;
		if (n == 0) return i;
	} while (i-- != 0);

	return string::npos;
}


string read_string_from_FILE(FILE * file, size_t max_length /* = -1 */)
{
	vector<char> v;
	v.reserve(256);

	while (true) 
	{
		int nextchar = fgetc(file);
		if (nextchar == '\0' || nextchar == EOF)
			break;
		if (v.size() < max_length)
			v.push_back(nextchar);
	}

	if (v.size() == max_length)
	{
		v.push_back('.');
		v.push_back('.');
		v.push_back('.');
	}

	v.push_back('\0');

	return string(&v[0]);
}

void write_string_to_FILE(FILE * file, const char * str)
{
	fflush(file);
	size_t i = 0;
	do
	{
//		cout << (int)str[i] << ' ';
		fputc(str[i], file);

		// We use a do-while because we want the \0 to be written to the stream
		// for sending multiple strings
	} while (str[i++] != 0);

//	cout << endl;

	fflush(file);
}



/**
*
*
**/

string readFile(const string & filename)
{
	ifstream file;
	file.open(filename.c_str());
	if (!file.good())
		return "";
	
	stringbuf linebuf;
	file.get(linebuf, '\0');
	linebuf.pubsync();
	return linebuf.str();
}


void readConfig(const string & testsFolder, FileMap & map, const string & discriminator /* = "" */)
{
	string file;
	if (testsFolder == "" || testsFolder[testsFolder.length()-1] == '/')
		file = testsFolder + "config.ini";
	else
		file = testsFolder;
	readFileGeneric(file, &map, NULL, discriminator);
}

void readFile(const string & file, vector<string> & lines)
{
	readFileGeneric(file, NULL, &lines);
}

void readFileGeneric(const string & filename, FileMap * map, vector<string> * lines, const string & discriminator /* = "" */)
{
	ifstream infile;
	istream * fileptr;
	if (filename == "/dev/stdin")
		fileptr = &cin;
	else
	{
		fileptr = &infile;
		infile.open(filename.c_str(), fstream::in);
	}
	istream & file = *fileptr;

	vector<string> * section = NULL;
	if (map != NULL) section = &(*map)[""];
	else section = lines;

	while ((file.good() && file.peek() == '\n') || file.peek() == '\r')
		file.get(); // get '\n'

	while (file.good())
	{
		// Read a line - A lot of code, I know, right?
		stringbuf linebuf;
		file.get(linebuf);
		while ((file.good() && file.peek() == '\n') || file.peek() == '\r')
			file.get(); // get '\n'
		linebuf.pubsync();
		string line = linebuf.str();
		int len = line.length();
		if (len == 0) continue;

        if (line[len-1] == '\r')
            line.replace(--len,1,"");

		if (len == 0 || line[0] == ';') continue; // skip comments
		
		if (map != NULL)
		{
			// Update the section
			if (line[0] == '[' && line[len-1] == ']')
			{
				section = &(*map)[line.substr(1, len - 2)];
				continue;
			}
			else if (line[0] == '[' || line[len-1] == ']')
			{
				cout << "config.ini: Format error: " << line << endl;
				exit(-1);
			}
		}

		// Or add the line/file to the section
		size_t delim_pos = line.find_first_of("?:");
		if (delim_pos == string::npos || map == NULL)
			section->push_back(line);
		else if ((line[delim_pos] == ':' && (delim_pos == 0 || discriminator == "")) ||
		         line.compare(0, delim_pos, discriminator) == 0)
			section->push_back(line.substr(delim_pos+1, line.size()-delim_pos-1));
	}

	if (filename != "/dev/stdin")
		infile.close();
}


OptionsParser::OptionsParser()
{
	valueMap[""]      = true;

	valueMap["yes"]   = true;
	valueMap["no"]    = false;

	valueMap["on"]    = true;
	valueMap["off"]   = false;

	valueMap["true"]  = true;
	valueMap["false"] = false;

	valueMap["1"]     = true;
	valueMap["0"]     = false;
}

vector<string> OptionsParser::parse(int argc, const char * const * argv)
{
	vector<string> unprocessedArgs;
	size_t out_arg_i = 0;

	for (int arg_i = 1; arg_i < argc; arg_i++)
	{
		string originalCaseArg = argv[arg_i];
		string currarg = toLower(originalCaseArg);

		if (currarg.compare(0, 2, "--") == 0) //long option
		{
			bool invert = (currarg.compare(2, 2, "no") == 0);
			size_t name_i = (invert ? 4 : 2);
			size_t equalspos = currarg.find_first_of("=-", name_i);
			
			string name = currarg.substr(name_i, equalspos - name_i);
			string value = (equalspos >= currarg.length()) ? "" : currarg.substr(equalspos);

			optsMap_t::iterator option = optsMap.find(name);
			if (option == optsMap.end())
			{
				cerr << "Unknown option: " << currarg << endl;
				exit(-1);
			}

			valueMap_t::iterator valueIt = valueMap.find(value);
			if (valueIt == valueMap.end())
			{
				cerr << "Unknown value: " << currarg << endl;
				exit(-1);
			}

			*option->second = valueIt->second ^ invert;
		} // "--"

		else if (currarg[0] == '-') //string of single char options
		{
			for (size_t c = 1; currarg[c] != '\0'; c++)
			{
				optsMap_t::iterator option = optsMap.find(string(1,currarg[c]));
				if (option == optsMap.end())
				{
					cerr << "Unknown option: -" << currarg[c] << endl;
					exit(-1);
				}
				*option->second = true;
			}
		}

		else //positional argument
		{
			if (out_arg_i < args.size())
				*args[out_arg_i] = originalCaseArg;
			else
				unprocessedArgs.push_back(originalCaseArg);
			out_arg_i++;
		}
	}
	
	return unprocessedArgs;
}

char * processOptions(int argc, char ** argv, OptionsMap & opts, vector<string> & args)
{
	for (int arg_i = 1; arg_i < argc; arg_i++)
	{
		char * currarg = argv[arg_i];

		if (strncmp(currarg, "--", 2) == 0) //long option
		{
			bool value, invert;
			size_t string_i;

			if (strncasecmp(currarg+2, "no", 2) == 0)
			{
				invert = true;
				string_i = 4;
			}
			else
			{
				invert = false;
				string_i = 2;
			}
			
			size_t equals_i = string_i;
			while (currarg[equals_i] != '\0' && currarg[equals_i] != '=')
				equals_i++;
			if (currarg[equals_i] == '=')
				currarg[equals_i++] = '\0';

			OptionsMap::iterator option = opts.find(currarg+string_i);

			if (option == opts.end())
			{
				cerr << "Unknown option: " << currarg << endl;
				return currarg;
			}

			char valuechar = tolower(currarg[equals_i]);
			if (valuechar == 'o') valuechar = tolower(currarg[equals_i+1]) + 1;
			switch (valuechar)
			{
				case '\0'  : value = true;  break;
				case 'f'+1 : value = false; break; //off: see 'o' above
				case 'n'   : value = false; break;
				case 'n'+1 : value = true;  break; //on: contrast 'n': see 'o' above
				case 't'   : value = true;  break;
				case 'y'   : value = true;  break;
				default:
					cerr << "Unknown option value: " << currarg << endl;
					return currarg;
			}

			(*option).second = value ^ invert;
		} // "--"

		else if (currarg[0] == '-') //string of single char options
		{
			for (size_t c = 1; currarg[c] != '\0'; c++)
			{
				OptionsMap::iterator option = opts.find(string(1,currarg[c]));
				if (option == opts.end())
				{
					cerr << "Unknown option: -" << currarg[c] << endl;
					currarg[1] = currarg[c];
					currarg[2] = '\0';
					return currarg;
				}
				(*option).second = true;
			}
		}

		else //positional argument
			args.push_back(currarg);
	}
	
	return NULL;
}



void makeLower(string & str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
}

string toLower(const string & str)
{
	string s(str);
	makeLower(s);
	return s;
}



/**
*  A wrapper function which writes a buffer to a file.
**/
ssize_t writeBytesToFile(signed int fileDescriptor, const char * buffer, unsigned int bufferLength) {
	return writen(fileDescriptor, buffer, bufferLength);
}


// From Steven's Unix Net Programming
// http://www.kohala.com/start/
/* Write "n" bytes to a descriptor. */
ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t         nleft;
	ssize_t        nwritten;
	const int8_t * ptr;

	ptr = static_cast<const int8_t*>(vptr);
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = ::write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return -1; /* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return n;
}




// From Steven's Unix Net Programming
// http://www.kohala.com/start/
/* Read "n" bytes from a descriptor. */
ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t   nleft;
	ssize_t  nread;
	int8_t * ptr;

	ptr = static_cast<int8_t*>(vptr);
	nleft = n;
	while (nleft > 0) {
		if ( (nread = ::read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return -1;
		}
		else if (nread == 0)
			break; /* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return n - nleft; /* return >= 0 */
}


// TODO (toole1): This should be moved to monad since it's very
// namespace specific and unlikely to be used similarly elsewhere
void rename_main(const string & file, const string & newname)
{
	assertExists(file);
	exec( "sed", "-i", "-e",
	      ( "s/int[\\r\\n \\t][\\r\\n \\t]*main(.*)/namespace proxy_test { int " + newname +
		    "(int argc, char ** argv); } int proxy_test::" + newname + "(int argc, char ** argv)/" ).c_str(),
	      file.c_str() );
}

vector<string> tokenize(const string & str, char delim)
{
	vector<string> args;
	
	size_t start = 0;
	size_t end;
	for (end = str.find(delim); end != string::npos; end = str.find(delim, start))
	{
		args.push_back(str.substr(start, end - start));
		start = end+1;
	}
	args.push_back(str.substr(start, str.size() - start));
	
	return args;
}

vector<string> tokenize(const string & str, const string & delims)
{
	vector<string> args;
	
	size_t start = 0;
	while (start < str.length() && delims.find(str[start]) != string::npos) start++;
	size_t end;
	for (end = str.find_first_of(delims); end != string::npos; end = str.find_first_of(delims, start))
	{
		args.push_back(str.substr(start, end - start));
		start = end+1;
		while (start < str.length() && delims.find(str[start]) != string::npos) start++;
	}
	if (start < str.length())
		args.push_back(str.substr(start, str.length() - start));
	
	return args;
}

namespace colorize
{
const char * BLACK = "\033[39m";
const char * GREEN = "\033[32m";
const char * RED   = "\033[31m";
const bool is_color_enabled = isatty(STDOUT_FILENO);


}

} // namespace util

