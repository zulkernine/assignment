class Student {
  final int roll;
  String deptCode;
  String name;
  String phone;
  String address;

  Student({required this.roll, required this.deptCode, required this.name, required this.phone, required this.address});

  Student.temp(this.roll):deptCode='CSE01A',name='',phone='',address='';

  Student.from(Student st)
      : this(roll: st.roll, deptCode: st.deptCode, name: st.name, phone: st.phone, address: st.address);
}
