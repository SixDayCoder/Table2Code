# Table2Code
<br>Table To Cplusplus Code Generator</br>
<br>support for 4 val types<br>
* INT32
* INT64
* STRING
* FLOAT


# Directory
## generate
<br>generate dir contains some xml files and python source files for generating xxx.cpp file</br>
<br>`TableGenerateTemplate_Header.xml` -> generate table_xxxx.h</br>
<br>`TableGenerateTemplate_Impl.xml`   -> generate table_impl.cpp</br>
<br>`TableGenerateTemplate_ImplManager.xml` -> generate table_manager.cpp</br>
## src
cpp source files dir
## tables
table source dir

# How To Use
we can make a new table named `Item.txt` and open it with Excel.
![Excel](https://github.com/SixDayCoder/MarkDownIMG/blob/master/table2code/1.png)
<br>Put `Item.txt` into `tables dir`</br>
<br>Then execute `main.py` in `generate` dir</br>
<br>You will find `table_item.h` `table_impl.cpp` `table_manager.cpp` in `tables\generate`, just like this:
![Excel](https://github.com/SixDayCoder/MarkDownIMG/blob/master/table2code/2.png)
<br>Move all files in tables\generate to `src\tables`.</br>
<br>Finally, you call `TableManager::Load` to load `Item.txt` from disk to memory, and use the macros defined in `table_instance.h` to access.</br>

# Example
<br>Use `TABLE_GET_COUNT(Table_Item) to Get Item.txt line number </br>
<br>Use `TABLE_GET_BY_INDEX(Table_Item) to iterator every single line in Item.txt </br>
<br>Use `TABLE_GET_BY_ID(Table_Item)(nId) to get one line by id in Item.txt </br>

```
#include "table\table_item.h"
for(int32_t i = 0; i < TABLE_GET_COUNT(Table_Item); ++i) {
    const Table_Item* record = TABLE_GET_BY_INDEX(Table_Item)(i);
    if(record != nullptr) {
        cout << record->GetId() << " " << record->GetPrice() << " " << record->GetStackCount() << " " << record->GetDataId() << endl;
    }
}
const Table_Item* record = TABLE_GET_BY_ID(Table_Item)(nId);
```

# Notice
<br>1.For now, `Table2Code` only support for 4 types which is :</br>
* INT32
* INT64
* STRING
* FLOAT

<br>2.The first field is Id and the second field is Desc, which can not be changed!</br>
<br>3.`Table2Code` support for array, for more details you can find it in `table\Aarray.txt` `src\table\table_array.h`