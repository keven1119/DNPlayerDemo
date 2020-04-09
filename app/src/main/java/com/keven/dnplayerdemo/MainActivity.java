package com.keven.dnplayerdemo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Toast;

import com.dongnao.live.LiveManager;
import com.dongnao.live.list.LiveList;
import com.dongnao.live.room.Room;
import com.dongnao.live.room.Videoinfo;
import com.google.android.material.tabs.TabLayout;
import com.trello.rxlifecycle2.android.ActivityEvent;
import com.trello.rxlifecycle2.components.support.RxAppCompatActivity;

import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.schedulers.Schedulers;
import io.reactivex.subscribers.DisposableSubscriber;

public class MainActivity extends RxAppCompatActivity implements View.OnClickListener {

    private TabLayout tabLayout;
    private RecyclerView recyclerView;
    private LiveAdapter liveAdapter;

    private DNPlayer dnPlayer;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        // 配置recycleview
//        recyclerView = findViewById(R.id.recycleView);
//        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
//        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
//        recyclerView.setLayoutManager(layoutManager);
//        liveAdapter = new LiveAdapter(this);
//        liveAdapter.setItemClickListener(this);
//        recyclerView.setAdapter(liveAdapter);
//
//        //配置tab
//        tabLayout = findViewById(R.id.tabLayout);
//        tabLayout.addOnTabSelectedListener(this);
//        //添加标签
//        addTabs();

        findViewById(R.id.start_btn).setOnClickListener(this);

        SurfaceView surfaceView = findViewById(R.id.surfaceView);
        dnPlayer = new DNPlayer();
        dnPlayer.setSurfaceView(surfaceView);
        dnPlayer.setDataSource("rtmp://58.200.131.2:1935/livetv/hunantv");
        dnPlayer.setOnPrepareListener(new DNPlayer.OnPrepareListener() {
            @Override
            public void onPrepare() {
//                runOnUiThread(new Runnable() {
//                    @Override
//                    public void run() {
//                        Toast.makeText(MainActivity.this, "可以开始播放了", Toast.LENGTH_LONG).show();
//                    }
//                });

                dnPlayer.start();
            }
        });
    }

    @Override
    public void onClick(View v) {

        dnPlayer.prepare();
    }

//    private void addTabs() {
//        addTab("lol", "英雄联盟");
//        addTab("acg", "二次元");
//        addTab("food", "美食");
//    }
//
//    private void addTab(String tag, String title) {
//        TabLayout.Tab tab = tabLayout.newTab();
//        tab.setTag(tag);
//        tab.setText(title);
//        tabLayout.addTab(tab);
//    }
//
//
//    @Override
//    protected void onDestroy() {
//        super.onDestroy();
//        tabLayout.removeOnTabSelectedListener(this);
//    }
//
//    /**
//     * 切换标签回调
//     *
//     * @param tab
//     */
//    @Override
//    public void onTabSelected(TabLayout.Tab tab) {
//        LiveManager.getInstance()
//                .getLiveList(tab.getTag().toString())
//                .compose(this.<LiveList>bindUntilEvent(ActivityEvent.DESTROY))
//                .subscribeOn(Schedulers.io())
//                .observeOn(AndroidSchedulers.mainThread())
//                .subscribe(new DisposableSubscriber<LiveList>() {
//
//                    @Override
//                    public void onNext(LiveList liveList) {
//                        liveAdapter.setLiveList(liveList);
//                        liveAdapter.notifyDataSetChanged();
//                    }
//
//                    @Override
//                    public void onError(Throwable t) {
//                        t.printStackTrace();
//                    }
//
//                    @Override
//                    public void onComplete() {
//
//                    }
//                });
//
//    }
//
//    @Override
//    public void onTabUnselected(TabLayout.Tab tab) {
//
//    }
//
//    @Override
//    public void onTabReselected(TabLayout.Tab tab) {
//
//    }
//
//    @Override
//    public void onItemClick(String id) {
//        LiveManager.getInstance()
//                .getLiveRoom(id)
//                .compose(this.<Room>bindUntilEvent(ActivityEvent.DESTROY))
//                .subscribeOn(Schedulers.io())
//                .observeOn(AndroidSchedulers.mainThread())
//                .subscribe(new DisposableSubscriber<Room>() {
//
//
//                    @Override
//                    public void onNext(Room room) {
//                        Videoinfo info = room.getData().getInfo().getVideoinfo();
//                        String[] plflags = info.getPlflag().split("_");
//                        String room_key = info.getRoom_key();
//                        String sign = info.getSign();
//                        String ts = info.getTs();
//                        Intent intent = new Intent(MainActivity.this, PlayActivity.class);
//                        String v = "3";
//                        if (null != plflags && plflags.length > 0) {
//                            v = plflags[plflags.length - 1];
//                        }
//                        intent.putExtra("url", "http://pl" + v + ".live" +
//                                ".panda.tv/live_panda/" + room_key
//                                + "_mid" +
//                                ".flv?sign=" + sign +
//                                "&time=" + ts);
//                        startActivity(intent);
//                    }
//
//                    @Override
//                    public void onError(Throwable t) {
//                        t.printStackTrace();
//                    }
//
//                    @Override
//                    public void onComplete() {
//
//                    }
//                });
//    }
}

