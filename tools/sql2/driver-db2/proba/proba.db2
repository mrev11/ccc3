connect to sample;

--select schemaname, owner from syscat.schemata;
--drop schema konto restrict;
--create schema konto authorization vermes;

set schema konto;
list tables for schema konto;
describe table proba;
select * from konto.proba;
values nextval for seqproba;
