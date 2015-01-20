
list node directory;
list database directory;


connect to proba1;
get connection state;
select schemaname, owner from syscat.schemata;
list tables;


connect to sample;
get connection state;


values(user,current_schema);
set current_schema = 'XXX';
values(user,current_schema);

set current_schema = 'vermes';
values(user,current_schema);

select schemaname, owner from syscat.schemata order by schemaname;
list tables;
describe table vermes.employee;




--terminate;

