#!/usr/bin/ruby

require 'sqlite3'

db=SQLite3::Database.new('tesztdb')
db.execute("PRAGMA journal_mode=WAL")

create=<<-EOS 
CREATE TABLE proba( 
  szamla varchar(24) collate rtrim not null 
 ,devnem char(3) collate rtrim
 ,megnevezes varchar(30) collate rtrim
 ,osszeg numeric(17,2)
 ,tulmenflag boolean
 ,konyvkelt date
 ,megjegyzes blob
)
EOS

begin
    db.execute("drop table proba")
rescue SQLite3::Exception => err
    puts err
end

db.execute(create) 
db.execute("CREATE UNIQUE INDEX proba_primarykey on proba (szamla,devnem)")
db.execute("CREATE INDEX proba_nev on proba (megnevezes,szamla)")

db.transaction
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('000000000000000000000000','HUF','BLACK')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('111111111111111111111111','HUF','WHITE')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('222222222222222222222222','HUF','WHITE')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('333333333333333333333333','HUF','BLACK')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('444444444444444444444444','HUF','WHITE')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('555555555555555555555555','HUF','WHITE')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('666666666666666666666666','HUF','BLACK')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('777777777777777777777777','HUF','WHITE')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('888888888888888888888888','HUF','WHITE')")
    db.execute("insert into proba (szamla,devnem,megnevezes) values ('999999999999999999999999','HUF','BLACK')")
db.commit


db.transaction
    puts "What is in the table?"
    cnt=-1
    db.execute("select szamla,megnevezes from proba") do |row|
        print cnt+=1," ",row[0]," ",row[1],"\n"
    end
    
    
    puts "Updates"
    cnt=-1
    db.execute("select szamla,megnevezes from proba") do |row|  #(select)
        print cnt+=1," ",row[0]," ",row[1],"\n"
        db.execute( "update proba set megnevezes=? where szamla=?", row[1]+"*", row[0] ) #(update)
        if( cnt<20 )
            sleep(1)
        else
            break  #no endless loop
        end
    end
        
    
    puts "What is in the table?"
    cnt=-1
    db.execute("select szamla,megnevezes from proba") do |row|
        print cnt+=1," ",row[0]," ",row[1],"\n"
    end
db.rollback
    
puts "Cleanup"
db.close



# Counter examples and other variations:
#
# 1) Use version 3.7.9 of libsqlite3.so (instead of current one).
#
# 2) Replace line 54 (select) with
# db.execute("select szamla,megnevezes from proba order by devnem") do |row|
# (there is an additional order by clause in it)
#
# 3) Omit line 56 (update) entirely
#
# 4) Replace line 56 (update) with
# db.execute( "update proba set megnevezes=? where szamla=?", row[1]+"", row[0] )
# ('*' is omitted from the update statement)


# Test results on various environments:
#
# 3.7.9     Precise         ok
# 3.8.7     Raspbian        regression
# 3.11.0    Xenial          regression
# 3.17.0    Windows 10      regression




