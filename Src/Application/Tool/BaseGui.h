#pragma once
#include <any>

//floatスライダー
struct SliderFloatInfo
{
	float* m_data = nullptr;

	float m_max = 0;
	float m_min = 0;
};

//intスライダー
struct SliderIntInfo
{
	int* m_data=nullptr;

	int m_max=0;
	int m_min=0;
};

struct DragFloatInfo
{
	float* m_data=nullptr;

	float m_col=0.f;
};


class BaseGui
{
public:
	BaseGui(std::string_view a_name) { m_name = a_name;}
	~BaseGui() {}

	virtual void Init();
	virtual void ChildUpdate() {}

	void Update();



	struct Data
	{
		std::string_view m_name{};
		std::any m_data{};
	};



	//データを格納
	template<typename T>
	void SetVar(const std::string_view a_dataType, const std::string_view& a_name, T* a_value)
	{
		//データタイプで探す
		auto _dataList = m_dataList.find(a_dataType);

		//なかったらデータタイプを登録
		if (_dataList == m_dataList.end())
		{
			std::vector<Data> _newData;
			m_dataList[a_dataType.data()] = _newData;

			_dataList = m_dataList.find(a_dataType);
		}

		
		
		Data _data(a_name, a_value);
		//m_guiData.push_back(_data);
		_dataList->second.push_back(_data);
	}

	void SetSliderFloat(const std::string_view a_dataType, const std::string_view& a_name, float* a_data,float a_min,float a_max)
	{
		//データタイプで探す
		auto _dataList = m_dataList.find(a_dataType);

		//なかったらデータタイプを登録
		if (_dataList == m_dataList.end())
		{
			std::vector<Data> _newData;
			m_dataList[a_dataType.data()] = _newData;

			_dataList = m_dataList.find(a_dataType);
		}

		SliderFloatInfo _slider(a_data, a_min, a_max);
		Data _data(a_name, _slider);

		_dataList->second.push_back(_data);
	}
	void SetDragFloat(const std::string_view a_dataType, const std::string_view& a_name, float* a_data, float a_col)
	{
		
			//データタイプで探す
			auto _dataList = m_dataList.find(a_dataType);

			//なかったらデータタイプを登録
			if (_dataList == m_dataList.end())
			{
				std::vector<Data> _newData;
				m_dataList[a_dataType.data()] = _newData;

				_dataList = m_dataList.find(a_dataType);
			}

			DragFloatInfo _infoData(a_data, a_col);

			Data _data(a_name, _infoData);
			_dataList->second.push_back(_data);
	}


protected:

	//guiウィンドウ名
	std::string_view m_name;


	std::unordered_map<std::string_view, std::vector<Data>> m_dataList;
	std::vector<Data> m_guiData;

};
