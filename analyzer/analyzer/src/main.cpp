
#include <gflags.h>

#include <iostream>
#include <string>
#include <config.h>
#include <analyzer.h>

DEFINE_string(action, "test", "");
DEFINE_string(src, "records/00000000_000_000.info", "");


void test() {
	if (FLAGS_src == "") {
		COUT_ERRO << "Missing file path, please set --src" << std::endl;
		return;
	}
	analyzer::Infos info;
	info.init(FLAGS_src);
	info.print();
}

static void failureFunction() { exit(0); }

int main(int argc, char *argv[]) {


	gflags::ParseCommandLineFlags(&argc, &argv, true);

	std::cout << FLAGS_action << std::endl;
	if (FLAGS_action == "test") {
		test();
	}

	gflags::ShutDownCommandLineFlags();
	system("pause");
	return 0;
}