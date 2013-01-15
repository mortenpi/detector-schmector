#!/usr/bin/python
import cbind.deserialize as dsr

print dsr.test('bser.fout')

evs = dsr.deserialize('events.fout')
print 'Events:', len(evs)
#for e in evs:
#	print e
