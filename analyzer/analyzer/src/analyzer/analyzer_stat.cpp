
#include <analyzer/analyzer.h>
#include <emath/include/statistic.h>

namespace analyzer {

	unsigned int Infos::index(TYPE_STAT stat_type, TYPE_CONTENT data_content) {
		return ((int)data_content * (int)TYPE_STAT::END + (int)stat_type);
	}


	void Infos::compute(TYPE_STAT stat_type, TYPE_CONTENT data_content) {

		if (stat_type == TYPE_STAT::END) return;

		for (int i = 0; i < info.layers_size(); i++) {

			// index of stat
			const int idx = index(stat_type, data_content);
			auto ptr = info.mutable_layers(i)->mutable_stat(idx);

			if (ptr->value() != 0.0) continue;

			if (stat_type == TYPE_STAT::MAX) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::max(ArrayToVector(info.layers(i).grad())));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::max(ArrayToVector(info.layers(i).weight())));
			}

			if (stat_type == TYPE_STAT::MIN) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::min(ArrayToVector(info.layers(i).grad())));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::min(ArrayToVector(info.layers(i).weight())));
			}

			if (stat_type == TYPE_STAT::MEAN) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::mean(ArrayToVector(info.layers(i).grad())));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::mean(ArrayToVector(info.layers(i).weight())));
			}

			if (stat_type == TYPE_STAT::STD) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::std(ArrayToVector(info.layers(i).grad())));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::std(ArrayToVector(info.layers(i).weight())));
			}

			if (stat_type == TYPE_STAT::SUM) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::sum(ArrayToVector(info.layers(i).grad())));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::sum(ArrayToVector(info.layers(i).weight())));
			}

			if (stat_type == TYPE_STAT::VAR) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::var(ArrayToVector(info.layers(i).grad())));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::var(ArrayToVector(info.layers(i).weight())));
			}

			if (stat_type == TYPE_STAT::NORM_0) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::norm(ArrayToVector(info.layers(i).grad()), 0));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::norm(ArrayToVector(info.layers(i).weight()), 0));
			}

			if (stat_type == TYPE_STAT::NORM_1) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::norm(ArrayToVector(info.layers(i).grad()), 1));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::norm(ArrayToVector(info.layers(i).weight()), 1));
			}

			if (stat_type == TYPE_STAT::NORM_2) {
				if (data_content == TYPE_CONTENT::GRAD)
					ptr->set_value(emath::norm(ArrayToVector(info.layers(i).grad()), 2));
				if (data_content == TYPE_CONTENT::WEIGHT)
					ptr->set_value(emath::norm(ArrayToVector(info.layers(i).weight()), 2));
			}
		}
	}

	void Infos::compute_all(TYPE_CONTENT data_content) {

#ifdef __DEBUG_INFO_OUTPUT
		COUT_METD << "func: compute_all_stat" << std::endl;
#endif

		for (int i = 0; i < info.layers_size(); i++) {

			if (info.layers(i).type() == "batch_norm") continue;

#ifdef __DEBUG_INFO_OUTPUT
			COUT_WARN << "Compute stat of layer: " << info.layers(i).name() << std::endl;
#endif

			for (unsigned int j = (int)TYPE_STAT::MAX; j < (int)TYPE_STAT::END; j++) {
#ifdef __DEBUG_INFO_OUTPUT
				__FUNC_TIME_CALL(compute((TYPE_STAT)j, data_content), name_stat_type[(TYPE_STAT)j]);
#else
				compute((TYPE_STAT)j, data_content);
#endif
			}
		}
	}

	void Infos::compute_list(std::vector<TYPE_STAT> stat_list, TYPE_CONTENT data_content) {

#ifdef __DEBUG_INFO_OUTPUT
		COUT_METD << "func: compute_list_stat" << std::endl;
#endif

		for (int i = 0; i < info.layers_size(); i++) {

			if (info.layers(i).type() == "batch_norm") continue;

#ifdef __DEBUG_INFO_OUTPUT
			COUT_WARN << "Compute stat of layer: " << info.layers(i).name() << std::endl;
#endif

			for (unsigned int j = 0; j < stat_list.size(); j++) {
#ifdef __DEBUG_INFO_OUTPUT
				__FUNC_TIME_CALL(compute(stat_list[j], data_content), name_stat_type[stat_list[j]]);
#else
				compute((TYPE_STAT)stat_list[j], data_content);
#endif
			}
		}
	}

}