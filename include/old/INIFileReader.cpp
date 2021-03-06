//author white
//INIFileReader class source

#include <vector>

#include "INIFileReader.hpp"
#include <systems/Logger.hpp>

wg::systems::INIFileReader::INIFileReader() {
	//element_num_ = 0;
	data_.clear();
	filename_ = "";
}

wg::systems::INIFileReader::INIFileReader(const std::string filename) {
	INIFileReader();
	LoadFile(filename);
}

int wg::systems::INIFileReader::LoadFile(const std::string filename) {

	filename_ = filename;

	//ファイルオープン
	file_.open(filename,std::ios::in);
	if (!file_) {	//読み込み失敗
		Logger::warning("iniファイル" + filename + "の読み込みに失敗しました");
		return -1;
	}

	//行で読む
	std::string line;
	std::string section = "";
	INIFileReaderElements tmp;
	while (!file_.eof()) {
		//行読み込み
		std::getline(file_, line);

		int cur = 0;
		int cur2 = 0;
		const char *cline = line.c_str();

		//空白は飛ばす
		for (cur = 0; cline[cur] == ' '; cur++);
		
		
		switch (cline[cur]) {
		case '\n': continue;	//次の行へ
		case '\0': continue;	//次の行へ
		case ';': continue;		//次の行へ
		case '[':
			//セクション
			cur2 = ++cur;
			for (; cline[cur] != ']' && cline[cur] != '\0' && cline[cur] != '\n'; cur++);
			section = line.substr(cur2, cur - cur2);
			break;

		default:
			
			//走査
			tmp.section_ = section;
			
			
			for (cur2 = cur; cline[cur] != '=' && cline[cur] != '\0'; cur++);
			tmp.key_ = line.substr(cur2, cur - cur2);
			
			
			for (cur2 = cur + 1; cline[cur] != '\0' && cline[cur] != ';' && cline[cur] != '\n'; cur++);
			if (cur2 >= cur) tmp.value_ = "";
			else tmp.value_ = line.substr(cur2, cur - cur2);

			data_.push_back(tmp);

			break;
		}
		
	}

	file_.close();

	return 0;
}

void wg::systems::INIFileReader::Delete() {
	//全ての要素の開放
	data_.clear();
}



int wg::systems::INIFileReader::ReloadFile() {
	Delete();
	return LoadFile(filename_);
}

std::string wg::systems::INIFileReader::getValue(const std::string section, const std::string key, const std::string def_str) const {
	
	std::vector<INIFileReaderElements>::const_iterator p;

	for (p = data_.begin(); p != data_.end(); p++) {
		if (p->section_.compare(section) == 0 && p->key_.compare(key) == 0) return p->value_;
	}
	
	return def_str;
}

int wg::systems::INIFileReader::RewriteValue(const std::string section, const std::string key, std::string value) {

	//ファイルオープン
	file_.open(filename_, std::ios::in);
	if (!file_) {	//読み込み失敗
		Logger::warning("iniファイル" + filename_ + "の読み込みに失敗しました");
		return -1;
	}


	std::string line;
	std::vector<std::string> lines;
	while (!file_.eof()) {
		std::getline(file_, line);
		lines.push_back(line);
	}

	file_.close();


	file_.open(filename_, std::ios::out | std::ios::trunc);
	if (!file_) {	//読み込み失敗
		Logger::warning("iniファイル" + filename_ + "の書き込みに失敗しました");
		return -1;
	}


	//行で読む
	std::string sec = "";
	bool match_sec = (section == "" ? true : false);
	bool edited = false;
	std::string output;

	for (int i = 0; i < lines.size();i++) {
		//行読み込み
		line = lines[i];
		output = line;
		int cur = 0;
		int cur2 = 0;
		const char *cline = line.c_str();

		//空白は飛ばす
		for (cur = 0; cline[cur] == ' '; cur++);


		switch (cline[cur]) {
		case '\n': break;	//次の行へ
		case '\0': break;	//次の行へ
		case ';': break;		//次の行へ
		case '[':
			//セクション
			cur2 = ++cur;
			for (; cline[cur] != ']' && cline[cur] != '\0' && cline[cur] != '\n'; cur++);
			sec = line.substr(cur2, cur - cur2);
			if (match_sec == false) {
				if (sec == section) match_sec = true;
			}
			else {
				//マッチするものがなかった場合
				output = key + "=" + value + "\n" + output;
				edited = true;
				match_sec = false;
			}
			break;

		default:
			if (!match_sec) break;
			//key and value
			INIFileReaderElements tmp;

			//走査
			tmp.section_ = section;


			for (cur2 = cur; cline[cur] != '=' && cline[cur] != '\0'; cur++);
			tmp.key_ = line.substr(cur2, cur - cur2);

			if (tmp.section_ == section && tmp.key_ == key) {
				//ここが編集するポイント
				output = key + "=" + value;
				match_sec = false;
				edited = true;
			}


			break;
		}

		if (i < lines.size() - 1) output += "\n";
		file_.write(output.c_str(), output.length());

	}

	if (edited == false) {
		if(!match_sec) output = "\n\n[" + section + "]\n" + key + "=" + value;	//末尾に追加
		else output = key + "=" + value;
		file_.write(output.c_str(),output.length());
	}

	file_.close();

	return 0;
}